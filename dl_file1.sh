#!/bin/bash

# Load API key from configuration file
source /home/rick/.ssh/api/config.sh

# DeepL API endpoint URLs
deepl_api="https://api-free.deepl.com/v2/document"
target_lang="EN"

# Directory to search for PDF files
directory="./"

# Log file to save responses
log_file="./deepl_responses.json"
counter=0
# Function to check if jq is installed and install it if not
check_and_install_jq() {
  if ! command -v jq &> /dev/null; then
    echo "jq is not installed. Installing..."
    sudo apt-get update
    sudo apt-get install -y jq
  fi
}

# Check and install jq
check_and_install_jq



# Function to check the status of each document and update log file
check_document_status() {
  local document_id="$1"
  local document_key="$2"
  local document="$3"
  local response=$(curl -s -X POST "$deepl_api/$document_id" \
    --header "Authorization: DeepL-Auth-Key $DEEPL_API_KEY" \
    --header 'Content-Type: application/json' \
    --data "{
      \"document_key\": \"$document_key\"
    }")

  local status=$(echo "$response" | jq -r '.status')

    if [[ "$status" == "done" ]]; then
    echo "Document $document translation is done."
    
    # Download the translated file
    curl -s -X POST "$deepl_api/$document_id/result" \
    --header "Authorization: DeepL-Auth-Key $DEEPL_API_KEY" \
    --header 'Content-Type: application/json' \
    --data "{
      \"document_key\": \"$document_key\"
    }" -o "$document"

     if [ $? -eq 0 ]; then
      jq "del(.$document_id)" "$log_file" > temp.json && mv temp.json "$log_file"
     else
      counter=$((counter + 1)) 
     fi
    elif [[ "$status" == "translating" ]]; then
    local seconds_remaining=$(echo "$response" | jq -r '.seconds_remaining')
    echo "Document $document_id translation is still in progress. Estimated time remaining: $seconds_remaining seconds."
    elif [[ "$status" == "error" ]]; then
    local error_message=$(echo "$response" | jq -r '.message')
    echo "Error occurred for document $document_id: $error_message"
    # Log the error to a separate error log file
    echo "{\"document\": \"$document\", \"document_id\": \"$document_id\", \"error_message\": \"$error_message\"}" >> error.log
    # Remove the entry from the main log file
    jq "del(.$document_id)" "$log_file" > temp.json && mv temp.json "$log_file"
    else
    echo "Document $document_id translation is in an unknown state: $status"
    fi
}

#if counter is greater than 10 then exit
if [ $counter -gt 10 ]; then
  echo "Error: Failed to download translated file for document $document_id."
  exit 1
fi


# Read log file line by line and check status for each document
while IFS= read -r line; do
  document_id=$(echo "$line" | jq -r '.document_id')
  document_key=$(echo "$line" | jq -r '.document_key')
  document=$(echo "$line" | jq -r '.document')
  check_document_status "$document_id" "$document_key" "$document"
done < "$log_file"

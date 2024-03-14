#!/bin/bash

# Load API key from configuration file
source /home/rick/.ssh/api/config.sh

# DeepL API endpoint URLs
deepl_api_translate_url="https://api-free.deepl.com/v2/document"
deepl_api_status_url="https://api-free.deepl.com/v2/document"

target_lang="EN"

# Directory to search for PDF files
directory="./"

# Log file to save responses
log_file="./deepl_responses.json"

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

# Function to handle DeepL API request for translation and log response
translate_document() {
  local document="$1"
  local response=$(curl -s -X POST "$deepl_api_translate_url" \
    --header "Authorization: DeepL-Auth-Key $DEEPL_API_KEY" \
    -H "Content-Type: multipart/form-data" \
    -F "target_lang=$target_lang" \
    -F "file=@$document")
  
  # Extract document ID and key from response
  local document_id=$(echo "$response" | jq -r '.document_id')
  local document_key=$(echo "$response" | jq -r '.document_key')
  
  # Increment the incremental ID
  ((incremental++))

  # Save response to log file in JSON format
  echo "{\"id\": $incremental, \"document\": \"$document\", \"document_id\": \"$document_id\", \"document_key\": \"$document_key\", \"status\": \"pending\"}" >> "$log_file"
}

# Function to check the status of each document and update log file
check_document_status() {
  local document_id="$1"
  local document_key="$2"

  local response=$(curl -s -X POST "$deepl_api_status_url/$document_id" \
    --header "Authorization: DeepL-Auth-Key $DEEPL_API_KEY" \
    --header 'Content-Type: application/json' \
    --data "{
      \"document_key\": \"$document_key\"
    }")

  local status=$(echo "$response" | jq -r '.status')

  if [[ "$status" == "done" ]]; then
    echo "Document $document_id translation is done."
    # Add your action here when status is done
  elif [[ "$status" == "translating" ]]; then
    local seconds_remaining=$(echo "$response" | jq -r '.seconds_remaining')
    echo "Document $document_id translation is still in progress. Estimated time remaining: $seconds_remaining seconds."
    # Add your action here when status is translating
  elif [[ "$status" == "error" ]]; then
    local error_message=$(echo "$response" | jq -r '.message')
    echo "Error occurred for document $document_id: $error_message"
    # Add your action here when status is error
  else
    echo "Document $document_id translation is in an unknown state: $status"
    # Add your action here when status is unknown
  fi
}

# Execute script for each PDF file found
find "$directory" -type f -name "*.pdf" -exec sh -c '
  for file do
    translate_document "$file"
  done
' sh {} +

# Read log file line by line and check status for each document
while IFS= read -r line; do
  document_id=$(echo "$line" | jq -r '.document_id')
  document_key=$(echo "$line" | jq -r '.document_key')
  check_document_status "$document_id" "$document_key"
done < "$log_file"

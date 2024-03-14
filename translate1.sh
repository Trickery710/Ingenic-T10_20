#!/bin/bash

# Load API key from configuration file
source /home/rick/.ssh/api/config.sh

# DeepL API endpoint URLs
deepl_api_translate_url="https://api-free.deepl.com/v2/document"
deepl_api_status_url="https://api-free.deepl.com/v2/document"
target_lang="EN"

# Get file type and output file type from command line arguments with default values pdf and docx
file_type=${1:-pdf}
output_file=${2:-docx}

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
    -F "output_format=$output_file" \
    -F "file=@$document")
  
  # Extract document ID and key from response
  local document_id=$(echo "$response" | jq -r '.document_id')
  local document_key=$(echo "$response" | jq -r '.document_key')

  # Save response to log file in JSON format
  echo "{\"document\": \"$document\", \"document_id\": \"$document_id\", \"document_key\": \"$document_key\"}" >> "$log_file"
}


# Execute script for each file type found
items=$(find "$directory" -type f -name "*$file_type")
for item in $items; do
  translate_document "$item"
done


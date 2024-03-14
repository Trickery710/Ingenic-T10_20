#!/bin/bash



# Remove spaces from filenames
./c_to_txt.sh remove_spaces

# Convert files
./c_to_txt.sh convert

# List of file types to convert to English
file_types=(docx pptx xlsx pdf txt html htm)

# Loop through the file types and translate if necessary
for file_type in "${file_types[@]}"
do
    # Determine output file type
    if [ "$file_type" == "pdf" ]; then
        output_file="docx"
    else
        output_file="$file_type"
    fi
    
    # Translate files if necessary (using translate1.sh)
        # Assuming translate1.sh handles PDF to DOCX translation
    ./translate1.sh "$file_type" "$output_file"
done


#sl files
./dl_file1.sh


# Revert files (assuming you have a function in c_to_txt.sh to revert files)
./c_to_txt.sh revert


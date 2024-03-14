#!/bin/bash
# Convert all .c files to .txt files

convert_files () {
    # Find all .c files recursively
c_files=$(find . -type f -name "*.c")

# Loop through each .c file
for file in $c_files; do
  # Get the file name without the extension
  file_name=$file.txt
  # Convert the file to .c.txt
    mv "$file" "$file_name"
 done

 # Find all .c files recursively
c_files=$(find . -type f -name "*.h")

# Loop through each .c file
for file in $c_files; do
  # Get the file name without the extension
  file_name=$file.txt
  # Convert the file to .h.txt
    mv "$file" "$file_name"
 done

#convert .md to .md.txt
c_files=$(find . -type f -name "*.md")

# Loop through each .c file
for file in $c_files; do
  # Get the file name without the extension
  file_name=$file.txt
  # Convert the file to .c.txt
    mv "$file" "$file_name"
 done

}

revert_files () {
    # Find all .c.txt files recursively
c_files=$(find . -type f -name "*.c.txt")

# Loop through each .c.txt file
for file in $c_files; do
  # Get the file name without the extension
  file_name=${file%.txt}
  # Convert
    mv "$file" "$file_name"
    done

    # Find all .h.txt files recursively
c_files=$(find . -type f -name "*.h.txt")

# Loop through each .h.txt file
for file in $c_files; do
  # Get the file name without the extension
  file_name=${file%.txt}
  # Convert
    mv "$file" "$file_name"
    done

#revert .md.txt to .md
c_files=$(find . -type f -name "*.md.txt")

# Loop through each .c.txt file
for file in $c_files; do
  # Get the file name without the extension
  file_name=${file%.txt}
  # Convert
    mv "$file" "$file_name"
    done
    
}

# Find all files and directories recursively
remove_spaces () {
find . -depth -name '* *' -exec bash -c 'dir=$(dirname "{}") && base=$(basename "{}") && newname=$(echo "$base" | tr -d " ") && mv "{}" "$dir/$newname"' \;
}



#if main Check if the user wants to convert or revert the files

if [ "$1" == "convert" ]; then
  convert_files
elif [ "$1" == "revert" ]; then
  revert_files
elif [ "$1" == "remove_spaces" ]; then
  remove_spaces  
else
  echo "Usage: $0 [convert|revert|remove_spaces]"
  exit 1
fi

exit 0


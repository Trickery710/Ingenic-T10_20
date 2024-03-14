#!/bin/bash

# Define the directory to search recursively
directory="./"

# Define the directory to create the directory tree
old_directory="./old"

# Find all directories recursively and create directory tree in ./old/
find "$directory" -type d -exec sh -c '
for dir do
    # Create corresponding directory structure in ./old/
    mkdir -p "$2/${dir#"$1"}"
done
' sh "$directory" "$old_directory" {} +

# Find all files recursively and copy them with .old extension
find "$directory" -type f -exec sh -c '
for file do
    cp "$file" "$2/${file}.old"
done
' sh "$directory" "$old_directory" {} +


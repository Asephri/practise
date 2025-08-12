import os
import string

def count_words_in_file(file_path):
    try:
        # Open the file and read its contents
        with open(file_path, 'r', encoding='utf-8') as file:
            text = file.read()
        
        # Remove punctuation and strip extra spaces
        text = text.translate(str.maketrans('', '', string.punctuation))
        text = text.strip()

        # Split the text into words and count them
        words = text.split()

        return len(words)
    
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return 0

def count_words_in_input_folder():
    input_dir = 'input'  # Directory named 'input' (same as the script's location)
    total_word_count = 0  # Initialize total word count

    # Check if the input directory exists
    if not os.path.exists(input_dir):
        print(f"The directory 'input' does not exist.")
        return

    # Iterate through each file in the 'input' folder
    for filename in os.listdir(input_dir):
        file_path = os.path.join(input_dir, filename)
        
        # Only process .txt files
        if os.path.isfile(file_path) and filename.endswith('.txt'):
            try:
                word_count = count_words_in_file(file_path)
                print(f"Word count for {filename}: {word_count}")
                total_word_count += word_count  # Add the count to total
            except Exception as e:
                print(f"Error processing file {filename}: {e}")
    
    # Print the total word count after processing all files
    print(f"\nTotal word count for all files: {total_word_count}")

# Main function that loops the script
if __name__ == "__main__":
    while True:  # Infinite loop to keep the script running until Enter is pressed
        count_words_in_input_folder()
        
        # Prompt to restart or exit
        restart = input("\nPress Enter to restart the script, or type 'exit' to quit: ").strip().lower()
        if restart == 'exit':
            print("Exiting the script...")
            break  # Exit the loop and end the script

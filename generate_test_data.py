import os
import random

# Directories
dir_a = 'test_data/files_a'
dir_b = 'test_data/files_b'

# Output files
common_file = 'test_data/expected_common.txt'
a_only_file = 'test_data/expected_a_only.txt'
b_only_file = 'test_data/expected_b_only.txt'

# Ensure directories exist
os.makedirs(dir_a, exist_ok=True)
os.makedirs(dir_b, exist_ok=True)

def write_file(directory, filename, content):
    """Writes a file with the specified content."""
    with open(os.path.join(directory, filename), 'w') as f:
        f.write(content)

def generate_file_content(size_in_kb, content):
    """Generates a string that is roughly size_in_kb KB in size."""
    return content * (size_in_kb * 1024)  # 1KB = 1024 bytes

def generate_files(n, small_size=1, medium_size=5, large_size=100):
    """Generates n files in dir_a and dir_b, and creates the expected output files."""
    common_files = []
    a_only_files = []
    b_only_files = []

    for i in range(n):
        print(f"Generating file {i}/{n}")
        filename = f"file{i}.txt"
        
        # Randomly decide the file size category
        size_category = random.choice(["small", "medium", "large"])

        # Randomly decide if the file will be common or unique
        is_common = random.choice([True, False])

        if size_category == "small":
            content_a = generate_file_content(small_size, 'C')  # Small file
            content_b = content_a
        elif size_category == "medium":
            content_a = generate_file_content(medium_size, 'C')  # Medium file
            content_b = content_a
        else:
            content_a = generate_file_content(large_size, 'C')  # Large file
            content_b = content_a

        
        
        # Common file in both dirs
        if is_common:
            write_file(dir_a, filename, content_a)
            write_file(dir_b, filename, content_b)
            common_files.append(filename)
        
        # Unique to dir_a and dir_b
        else:
            content_a = content_b.replace('C', 'A') # Make file unique by changing content from C to A
            content_b = content_b.replace('C', 'B') # Make file unique by changing content from B to A
            write_file(dir_a, filename, content_a)
            write_file(dir_b, filename, content_b)
            a_only_files.append(filename)
            b_only_files.append(filename)
    
    # Write the expected results to common.txt, a_only.txt, b_only.txt
    with open(common_file, 'w') as cf:
        cf.write("\n".join([os.path.join(dir_a, f) for f in common_files]) + "\n")
    
    with open(a_only_file, 'w') as af:
        af.write("\n".join([os.path.join(dir_a, f) for f in a_only_files]) + "\n")
    
    with open(b_only_file, 'w') as bf:
        bf.write("\n".join([os.path.join(dir_b, f) for f in b_only_files]) + "\n")

    print(f"Generated {n} files in each directory.")
    print(f"Common files: {len(common_files)}")
    print(f"Unique to dir_a: {len(a_only_files)}")
    print(f"Unique to dir_b: {len(b_only_files)}")
    print("Expected result files created (common.txt, a_only.txt, b_only.txt).")

if __name__ == "__main__":
    n = 10000  # Number of files, adjust for testing
    generate_files(n)

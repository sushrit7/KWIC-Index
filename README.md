# KWIC Index Generator

This C++ program generates a Key Word In Context (KWIC) index for a given list of titles, considering a set of "words to ignore." KWIC indexing allows efficient human-friendly search of titles, listing each title once for every keyword occurring in it.

## Usage

### Cloning the Repository
1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com//sushrit7/KWIC-Index.git
   ```
### Compilation
1. Navigate to the project directory:

```bash
  cd KWIC-index
```
2. Compile the kwicindex.cpp file:

```bash
g++ -o kwicindex kwicindex.cpp
```
### Execution
1. Run the compiled executable:
```bash
./kwicindex
```
## Input
- The input file (titles.in) should contain a list of words to ignore followed by the titles, separated by the string "::".
- Each word appears in lowercase letters on a line by itself and is no more than 15 characters in length.
- Each title appears on a line by itself and may consist of mixed-case (upper and lower) letters. Words in a title are separated by whitespace.
- No title contains more than 15 words.
- Case (upper or lower) is irrelevant when determining if a word is to be ignored.
  
## Output
- The output file (titles.out) will contain a KWIC-index of the titles, with each title appearing once for each keyword in the title.
- The KWIC-index is alphabetized by keyword.
- If a word appears more than once in a title, each instance is a potential keyword.
- The keyword should appear in all upper-case letters. All other words in a title should be in lower-case letters.
- Titles in the KWIC-index with the same keyword should appear in the same order as they appeared in the input file.
- In the case where multiple instances of a word are keywords in the same title, the keywords should be capitalized in left-to-right order.
- All titles in the output should be listed left-justified.
  
## Sample Input
See titles.in for an example input.

## Sample Output
See titles.out for an example output.

## Contributing
Feel free to contribute to the project and suggest improvements to enhance the KWIC indexing experience!
Happy indexing!   

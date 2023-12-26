
/*
___________________________________________________________________________________________
For list of titles and a list of ``words to ignore'', the following program generates a KWIC 
index of the titles. In a KWIC-index, a title is listed once for each keyword that occurs in 
the title. This assignment is due Tuesday (10/17) at 10 PM
____________________________________________________________________________________________
Steps used:
1. Input the ignore keyword in a string vector and sorting it.
2. Input the title and keyword in a vector of struct. 
3. Capitalizing the keyword in the title.
4. Sorting the vector by KWIC keyword.
5. Reorder to the original order for only similar keywords.
5. Write the output file.
_______________________________________________________________________________________________
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct KWICEntry 
{
    string keyword;
    string title;
    int keywordPosition;
    float originalOrder;
};

// Function to convert a string to lowercase
string toLower(const string& str) 
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to convert a string to uppercase
void toUpper(  string& str) 
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}


// QuickSort partition function for vector of KWICEntry structs
int partition(vector<KWICEntry>& arr, int low, int high) 
{
    string pivot = arr[high].keyword;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) 
    {
        if (arr[j].keyword < pivot) 
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort partition function for vector of strings
int partition(vector<string>& arr, int low, int high) 
{
    string pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) 
    {
        if (arr[j] < pivot) 
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Template QuickSort function
template<class T>
void quickSort(vector<T>& arr, int low, int high) 
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Template function to perform a binary search on a sorted vector
template<class T>
bool binarySearch(const vector<T>& sortedList, const string& target) {
    int low = 0;
    int high = sortedList.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (sortedList[mid] == target) {
            return true; // Found
        } else if (sortedList[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

//Function to return a vectors with keywords, keyword position and the line 
vector<KWICEntry> getKeywordAndTitle(const string& line, vector<string> ignoreWords, float originalOrder)
{
    istringstream ss(line);
    vector<KWICEntry> newEntry;
    string word;
    int position = 0;
    //Checking word by word for ignore word and keywords
    while (ss >> word) 
    {
        if (!binarySearch(ignoreWords, word)) 
        {
            KWICEntry entry;
            entry.keyword = word;
            entry.title = line; 
            entry.keywordPosition = position;
            entry.originalOrder = originalOrder;
            newEntry.push_back(entry);
            originalOrder = originalOrder + 0.1;
        }
        position++;
    }
  return newEntry;
}

//Capitalizes the keyword in the line
void capitalizeKeywordInTitle(vector<KWICEntry>& entries)
{
    for (int i = 0; i < entries.size(); i++)
    {
        istringstream iss(entries[i].title);
        ostringstream oss;
        string word;
        int pos = 0;
        //Capitaliizing when the word positions match
        while (iss >> word)
        {
            if (pos == entries[i].keywordPosition)
            {
                toUpper(word);
                oss << word << " ";
            }
            else
            {
                oss << word << " ";
            }
            pos++;
        }
        entries[i].title = oss.str();
    }   
}

//Function to swap the same keywords to original position in the output as the input
void swapSimilarKeywords(vector<KWICEntry>& arr) 
{
    for (int i = 1; i < arr.size(); i++) 
    {
        if (arr[i].keyword == arr[i - 1].keyword) 
        {
            if (arr[i].originalOrder < arr[i - 1].originalOrder) 
            {
                swap(arr[i], arr[i - 1]);
                //More swaps for similar keywords to put them in order
                int j = i - 1;
                while (j > 0 && arr[j].keyword == arr[j - 1].keyword && arr[j].originalOrder < arr[j - 1].originalOrder) 
                {
                    swap(arr[j], arr[j - 1]);
                    j--;
                }
            }
        }
    }
}


int main() 
{
    ifstream inputFile("titles.in");
    ofstream outputFile("titles.out"); 
    if (!inputFile || !outputFile) 
    {
        cerr << "Error opening files." << endl;
        return 1;
    }
    vector<string> ignoreWords;
    string line;

    while (getline(inputFile, line)) 
    {
        // Removing trailing whitespace
        int start = 0;
        int end = line.length();
        while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\r')) 
        {
            end--;
        }
        line = line.substr(start, end - start);
        // Checking if the line equals "::"
        if (line == "::") 
        {
            break;
        }
        // Storing the line in the ignoreWords vector 
        if (!line.empty()) 
        {
            ignoreWords.push_back(toLower(line));
        }
    }
    //Sorting the ignoreWords for binary search
    quickSort(ignoreWords, 0, ignoreWords.size()-1); 

    vector<KWICEntry> entries;
    float originalOrder = 0;

    // Processing titles by adding the vector containg keywowrd and title
    while (getline(inputFile, line)) 
    {
        string lowercaseTitle = toLower(line);
        vector<KWICEntry> titleEntries = getKeywordAndTitle(lowercaseTitle, ignoreWords, originalOrder);
        entries.insert(entries.end(), titleEntries.begin(), titleEntries.end());
        originalOrder++;
    }
    //Capitalizing the keywords
    capitalizeKeywordInTitle(entries);

    // Sorting the KWIC index using quickSort
    quickSort(entries, 0, entries.size() - 1);

    swapSimilarKeywords(entries);

    // Outputting the KWIC index to title.out file
    for (int i = 0; i < entries.size(); i++) 
    {
    outputFile << entries[i].title << endl; 
    }

    inputFile.close();
    outputFile.close();
    
    return 0;
}

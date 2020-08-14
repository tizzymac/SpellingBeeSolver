#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <list>

std::set<std::string> loadDictionary() {
    std::ifstream file("<PATH TO DICTIONARY>");
    std::set<std::string> dict;

    copy(std::istream_iterator<std::string>(file),
         std::istream_iterator<std::string>(),
         inserter(dict, dict.end()));
    
    return dict;
}

void getAllValidCombos(std::set<std::string> *combos, char center, char set[], std::string prefix, int n, int k)
{
    // Base case: k is 0
    if (k == 0)
    {
        if (prefix.find(center) != std::string::npos)
            combos->insert(prefix);
        return;
    }
  
    // One by one add all characters from set and recursively call for k equals to k-1
    for (int i = 0; i < n; i++)
    {
        std::string newPrefix;
          
        // Next character of input added
        newPrefix = prefix + set[i];
          
        // k is decreased, because we have added a new character
        getAllValidCombos(combos, center, set, newPrefix, n, k - 1);
    }
}

std::set<std::string> getAllValidCombos(char center, char set[], int k, int n)
{
    std::set<std::string> combos;
    getAllValidCombos(&combos, center, set, "", n, k);
    return combos;
}

int main(int argc, const char * argv[]) {
    // Load dictionary
    std::set<std::string> dictionary = loadDictionary();
    
    // Take input
    char center;
    char allLetters[6];
    std::cout << "Enter center letter: ";
    std::cin >> center;
    allLetters[0] = center;
    std::cout << "Enter the other 6 letters: ";
    for (int i = 0; i < 6; i++) {
        std::cin >> allLetters[i];
    }
    
    std::cout << "\nPossible solutions: \n\n";
    
    // Generate all combos containing center letter
    std::set<std::string> combos;
    for (int i = 4; i <= 8; i++) {
        std::set<std::string> next = getAllValidCombos(center, allLetters, i, 7);
        combos.insert(next.begin(), next.end());
    }
    
    // Check if in dictionary
    for (std::string const& c : combos)
        if (dictionary.find(c) != dictionary.end())
            std::cout << c << "\n";
    
    return 0;
}

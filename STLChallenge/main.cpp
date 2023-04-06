// Section 20
// Challenge 4
// Identifying palindrome strings using a stack and queue
#include <cctype>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <iomanip>

bool is_palindrome(const std::string& s)  // s = palindrome || s = racecar
{
    // You must implement this function.
    // Since we are learning the STL - use a stack and a queue to solve the problem.
 
    std::queue<char> queue_pal; 
    std::stack<char> stack_pal; 

    for (auto c : s)
        if (isalpha(c)) {
            queue_pal.push(std::toupper(c)); // queue_pal = [ palindrome ] || queue_pal = [ racecar ]
            stack_pal.push(std::toupper(c)); // stack_pal = [ emordnilap ] || stack_pal = [ racecar ]
        }
  
    while (queue_pal.size() > 1 && stack_pal.size() > 1) {
        if (queue_pal.front() != stack_pal.top())
            return false; 
        queue_pal.pop(); 
        stack_pal.pop(); 
    }
    return true;
}

int main()
{
    std::vector<std::string> test_strings{"a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };
   
    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for(const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s)  << s << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
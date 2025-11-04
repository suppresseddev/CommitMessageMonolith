//
// Skeleton portion of the code.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <tuple>
#include "trie.h"
using namespace std;


void clearConsole() {
    //Resets Console
    std::cout << "\033[2J\033[1;1H";
}

int CONSOLE_WIDTH = 98;
int CONSOLE_INDENT = 10;
std::string test_paragraph1 = "Have you been tested before? Nay you are yet to be tested. I can see it in your eyes. Look at you. "
                             "I've already made arrangements for your testing. Take a deep breath, this won't hurt me as much as it does you. ";
std::string test_paragraph2 = "Relax, its a joke. We're just going to be testing your knowledge today. Alright, lets start with something simple... "
                            "what is six times three?";
std::string bar((CONSOLE_INDENT * 2 + CONSOLE_WIDTH + 2), '-');
void get_input(std::string& result) {
    std::cout << bar << std::endl;
    std::cout << '>';
    std::getline(std::cin, result);
}
void get_input() {
    std::string temp;
    std::cout << bar << std::endl;
    std::cout << '>';
    std::getline(std::cin, temp);
}

std::vector<std::string> textWrap(std::string messy_text) {
    std::vector<std::string> result;
    std::string temp = "";
    int count = 0;
    for (char c : messy_text) {
        count++;
        if (count >= CONSOLE_WIDTH) {
            if (c == ' ') {
                count = 0;
                result.push_back(temp);
                temp = "";
            } else {
                temp += c;
            }
        } else {
            temp += c;
        }
    }
    result.push_back(temp);
    return result;;
}
void print(std::string text) {
    std::string indent_gap(CONSOLE_INDENT, ' ');
    for (std::string line : textWrap(text)) {
        std::cout << indent_gap << line << std::endl;
    }
}
void printNewLine() {
    std::cout << std::endl;
}
void printHeader() {
    printNewLine();
    std::string gap1(46, ' ');
    std::cout << gap1 << "The Commit Message Monolith" << std::endl;
    std::string gap2(50, ' ');
    std::cout << gap2 << "Seek our knowledge." << std::endl;
    printNewLine();
    std::cout << bar << std::endl;
}

void printListing(std::vector<std::string> word_list, std::vector<float> freq_list) {
    for (int i = 0; i < word_list.size(); i++) {
        std::stringstream entry;
        entry << (i+1) << ". ";
        entry << word_list[i] << " <Frequency: " << std::fixed << std::setprecision(2) << freq_list[i] << ">" << std::endl;
        print(entry.str());
    }
}

void printEntry(std::string word, float freq) {
    std::stringstream entry;
    entry << word << " has a frequency of " << std::fixed << std::setprecision(2) << freq << "." << std::endl;
    print(entry.str());
}

int main() {
    //Before any of you (data structure designers) write any code here, put the name of your data structure next to a or b and stick to that.
    //A -> Trie
    //B -> (insert data structure name)

    //Startup

    //This section is for doing what you need to do for your classes to work.
    //Creating class/structs, parsing data, etc.
    //Stay within the timer objects (start/end) for the purposes of comparing performance.

    auto start_a =  std::chrono::high_resolution_clock::now();
    // For Data Structure Designer A
    // Creating Trie
    monolith_trie trie;

	// Parsing Words
	vector<string> files = {"data/CommitMessages_A.csv", "data/CommitMessages_B.csv", "data/CommitMessages_C.csv"};
	for (const auto& file_name : files) {
		ifstream file(file_name);
		if (!file.is_open()) {
			cerr << "Unable to open file" << endl;
			return 1;
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string word;
			vector<string> words;

			while (getline(ss, word, ',')) {
				words.push_back(word);
			}

			for (string elem : words) {
				trie.insert_sentence(elem);
			}
		}

		file.close();
	}
    //
    auto end_a = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> elapsed_a =  end_a - start_a;

    auto start_b = std::chrono::high_resolution_clock::now();
    // For Data Structure Designer B

    //
    auto end_b = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> elapsed_b =  end_b - start_b;

    //End of Startup

    bool running = true;
    //  Main Menu -> MAIN_MENU
    //  Top K -> TOP_K
    //  Bottom K -> BOT_K
    //  Identify K -> ID_K
    std::string cur_menu = "MAIN_MENU";

    while (running) {
        if (cur_menu == "MAIN_MENU")
        {
            clearConsole();
            printHeader();
            print("Type 1-3 for the following options, or type 'exit' to exit the program.");
            print("1. What are the top 'k' words?");
            print("2. What are the bottom 'k' words?");
            print("3. What of my word?");
            print("4. Show me the construction details.");
            std::string user_input;
            get_input(user_input);
            std::string valid[] = {"1", "2", "3", "4", "exit", "test"};
            bool valid_input = false;
            for (std::string option : valid) {
                if (user_input == option) {
                    valid_input = true;
                    if (option == "1") {
                        cur_menu = "TOP_K";
                    }
                    if (option == "2") {
                        cur_menu = "BOT_K";
                    }
                    if (option == "3") {
                        cur_menu = "ID_K";
                    }
                    if (option == "4") {
                        clearConsole();
                        printHeader();
                        print("So you wish to hear of our secrets.");
                        print("Very well. Those who know, share the sought knowledge.");

                        //Data Structure A
                        printNewLine();
                        std::stringstream text_a;
                        print("One voice speaks...");
                        text_a << "It took Data Structure A " << elapsed_a.count() << " ms to assemble itself.";
                        print(text_a.str());

                        //Data Structure B
                        printNewLine();
                        std::stringstream text_b;
                        print("Another voice speaks...");
                        text_b << "It took Data Structure B " << elapsed_b.count() << " ms to assemble itself.";
                        print(text_b.str());

                        get_input();
                    }
                    if (option == "exit") {
                        running = false;
                    }
                    if (option == "test") {
                        clearConsole();
                        printHeader();
                        print(test_paragraph1);
                        printNewLine();
                        print(test_paragraph2);
                        get_input();
                    }
                }
            }
            if (!valid_input && !user_input.empty()) {
                clearConsole();
                printHeader();
                print("You may only type 1, 2, 3, or exit.");
                get_input();
            }
        }
        else if (cur_menu == "TOP_K")
        {

            //Step 1

            std::string user_input;
            bool valid = false;
            while (!valid) {
                clearConsole();
                printHeader();
                print("So you would like to know what is best.");
                print("How many of the best words would you like to know?");

                get_input(user_input);
                valid = true;
                for (char c : user_input) {
                    if (std::isdigit(c) == false) {
                        valid = false;
                    }
                }
                if (user_input == "0") {
                    valid = false;
                }
                if (user_input == "") {
                    valid = false;
                }
                if (!valid) {
                    clearConsole();
                    printHeader();
                    print("You must enter a valid integer number greater than zero.");
                    get_input();
                }
            }

            //Step 2

            clearConsole();
            printHeader();
            //Pending completion of the other data structures.
            //Just do what you need to do to put the words and frequencies into their respective vectors.
            //THIS PORTION EXPECTS GREATEST -> LEAST
            //'k' is the target number of words.
            int k = std::stoi(user_input);

            auto start =  std::chrono::high_resolution_clock::now();
            //For Data Structure Designer A
            
            tuple<vector<string>, vector<float>> result = trie.top_k(k);

            std::vector<std::string> words_a = get<0>(result);
            std::vector<float> freqs_a = get<1>(result);
            
            //
            auto end =  std::chrono::high_resolution_clock::now();

            std::string text_a = "One voice speaks... (";
            std::chrono::duration<float, std::milli> elapsed =  end - start;
            text_a += std::to_string(elapsed.count());
            text_a += " ms)";
            print(text_a);
            printNewLine();
            printListing(words_a, freqs_a);

            start = std::chrono::high_resolution_clock::now();
            //For Data Structure Designer B
            std::vector<std::string> words_b;
            std::vector<float> freqs_b;
            //
            end = std::chrono::high_resolution_clock::now();

            std::string text_b = "Another voice speaks... (";
            elapsed =  end - start;
            text_b += std::to_string(elapsed.count());
            text_b += " ms)";
            print(text_b);
            printNewLine();
            printListing(words_b, freqs_b);

            get_input();
            cur_menu = "MAIN_MENU";
        }
        else if (cur_menu == "BOT_K")
        {

            //Step 1

            std::string user_input;
            bool valid = false;
            while (!valid) {
                clearConsole();
                printHeader();
                print("So you would like to know what is worst.");
                print("How many of the worst words would you like to know?");

                get_input(user_input);
                valid = true;
                for (char c : user_input) {
                    if (std::isdigit(c) == false) {
                        valid = false;
                    }
                }
                if (user_input == "0") {
                    valid = false;
                }
                if (user_input == "") {
                    valid = false;
                }
                if (!valid) {
                    clearConsole();
                    printHeader();
                    print("You must enter a valid integer number greater than zero.");
                    get_input();
                }
            }

            //Step 2

            clearConsole();
            printHeader();
            //Pending completion of the other data structures.
            //Just do what you need to do to put the words and frequencies into their respective vectors.
            //THIS PORTION EXPECTS LEAST -> GREATEST
            //'k' is the target number of words.
            int k = std::stoi(user_input);

            auto start =  std::chrono::high_resolution_clock::now();
            //For Data Structure Designer A
            
            tuple<vector<string>, vector<float>> result = trie.bottom_k(k);

            std::vector<std::string> words_a = get<0>(result);
            std::vector<float> freqs_a = get<1>(result);
            
            //
            auto end =  std::chrono::high_resolution_clock::now();

            std::string text_a = "One voice speaks... (";
            std::chrono::duration<float, std::milli> elapsed =  end - start;
            text_a += std::to_string(elapsed.count());
            text_a += " ms)";
            print(text_a);
            printNewLine();
            printListing(words_a, freqs_a);

            start = std::chrono::high_resolution_clock::now();
            //For Data Structure Designer B
            std::vector<std::string> words_b;
            std::vector<float> freqs_b;
            //
            end = std::chrono::high_resolution_clock::now();

            std::string text_b = "Another voice speaks... (";
            elapsed =  end - start;
            text_b += std::to_string(elapsed.count());
            text_b += " ms)";
            print(text_b);
            printNewLine();
            printListing(words_b, freqs_b);

            get_input();
            cur_menu = "MAIN_MENU";
        }
        else if (cur_menu == "ID_K")
        {

            //Step 1

            std::string user_input;
            bool valid = false;
            while (!valid) {
                clearConsole();
                printHeader();
                print("So you have a personal inquiry...");
                print("Tell us, what word are you curious about?");
                get_input(user_input);
                valid = true;
                if (user_input == "") {
                    valid = false;
                }
                if (!valid) {
                    clearConsole();
                    printHeader();
                    print("You must enter something.");
                    get_input();
                }
            }

            //Step 2

            clearConsole();
            printHeader();
            //Pending completion of the other data structures.
            //Just do what you need to do to put the frequency into its variable.
            //'search_target' is the target word.
            std::string search_target = user_input;

            auto start =  std::chrono::high_resolution_clock::now();
            //For Data Structure Designer A
            float freq_a = trie.identify(search_target);
            //
            auto end =  std::chrono::high_resolution_clock::now();

            std::string text_a = "One voice speaks... (";
            std::chrono::duration<float, std::milli> elapsed =  end - start;
            text_a += std::to_string(elapsed.count());
            text_a += " ms)";
            print(text_a);
            printNewLine();
            printEntry(search_target, freq_a);

            start = std::chrono::high_resolution_clock::now();
            //For Data Structure Designer B
            float freq_b;
            //
            end = std::chrono::high_resolution_clock::now();

            std::string text_b = "Another voice speaks... (";
            elapsed =  end - start;
            text_b += std::to_string(elapsed.count());
            text_b += " ms)";
            print(text_b);
            printNewLine();
            printEntry(search_target, freq_b);

            get_input();
            cur_menu = "MAIN_MENU";
        }
    }
    return 0;
}

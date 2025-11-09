# Welcome to the Commit Message Monolith! #
This program uses a database of 3 million commit messages to get the frequencies of words in commit messages!

Words with higher frequency should be preferred to ones with lower frequency.

## Running the Program ##
Clone the repository to your local system.

This program's dataset is exclusively available to UF students and is not permanent.

Link to download: https://uflorida-my.sharepoint.com/:u:/g/personal/elijah_simon_ufl_edu/EaMX6V9jQWJKh1D6dc66p_kB5WuB9LDghyDfx7BcMw0ivA?e=CJVB26

You can then extract the contents of data.rar into the repository so that the repository base directory contains a folder called 'data' with this structure:

**data/**

  **---CommitMessages_A.csv**
  
  **---CommitMessages_B.csv**
  
  **---CommitMessages_C.csv**
  
  **---note.txt**

If the link is down, you can find the original dataset here: https://www.kaggle.com/datasets/dhruvildave/github-commit-messages-dataset

The program uses the 'message' column, and only the columns 1 to 3,000,000.

Developers trimmed the data using OpenRefine into 3 files with 1,000,000 entries each. (Naming conventions above.)

## Compile & Run ##
Using CMake and CMakeLists.txt, compile and run the program. (Developers used Clion's 'CMake Application' Run Configuration.)

<img width="835" height="710" alt="image" src="https://github.com/user-attachments/assets/4b7556ba-7c42-4c4e-bf26-facd7d2cef9a" />

Alternatively, if you need to run the program in the console, run the following commands in cmd.

(Anything in "<>" is to your own discretion.)

`cd <repository>`

`mkdir <build_location>`

`cd <build_location>`

`cmake ..`

`cmake --<build_location>`

`./Monolith.exe`

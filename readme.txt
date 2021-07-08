ARYAN GHOBADI: ADDRESS BOOK SYSTEM:

The system written below in C++, using only the standard libraries, is able to process the full range of functionality desired, and was written in under 2 hours.

Top down explanation of functionality:
-The system is a command line interface, meaning that the address book is displayed in a user friendly form on the command line, and the user is able to input instructions on the interface
-The user can ADD a person, DELETE an entry, SEARCH by a parameter, or EXIT the program, updating a local txt file which saves the current state of the address vector.
-On startup, this txt file is parsed again, and a fresh address vector is generated, to ensure data is consistent and up to date.

Extra comments, bugs or food for thought:
-I would ideally like to improve the readability of the search function or try to make it more efficeint, perhaps reduce it to O(nlogn) or less by using HashMaps if I had more time.
-There is a smaller bug which is caught in an edge case where names are contained in other names and additionally found in search (For instance, Finding ARYAN after searching for RYAN).
-I diagnosed the above bug as an issue with string reading, and with more time I would have been able to fix the bug, however it is a specific edge case that does not affect overall user interaction.
-I would also like to work on making the use time and startup time faster by using faster iteration algorithms, potentially by using other libraries if allowed in the future (outside of just Boost library)/

Usage instructions:
-No extra files required, simply compile the C++ file using GCC compiler if pre-installed, and using CodeRunner on VSCode.
-A makefile is also provided with the zip, simply typing make addressbook (this won't work very well on windows devices, which is why I have included the final EXE as well for simplicity.)
-Alternatively, if you cannot compile the project or make it, just run the final exe version which is also there.
-In the zip you will also find the original source code.
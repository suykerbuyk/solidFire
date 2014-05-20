Super Simple File Indexer
Create a multi‐threaded text file indexing command line application that works as follows:
1. Accept as input a file path (e.g. /myfiles) on the comand line
2. Have one thread that is responsible for searching the file path, including any sub‐directories, for text files (ending in .txt)
3. When a text file is found, it should be handed off to a worker thread for processing, and the search thread should continue searching.
4. There should be a fixed number (N) of worker threads (say, N=3) that handle text file processing.
5. When a worker thread receives a text file to process, it opens the file and reads the contents one word at a time. Words are delimited by any character other than A‐Z, a-z or 0‐9.
6. A master table in memory, shared between all threads, keeps track of all unique words encountered and the number of times it was encountered. Each time a word is encountered the count is incremented (or it is added to the table if not present). Words should be matched case‐insensitive and without any punctuation.
7. Once the file search is complete and all text files finish processing, the program prints out the top 10 words and their counts.  
Basically we just want to find the top 10 words across a directory tree of text files.


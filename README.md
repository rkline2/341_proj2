# Indexing using BSTs and overloading

## Objectives
The objective of this programming assignment is to have you practice using Binary Search Trees, Recursion, Queues, Strings, 
Overloaded operators, and File I/O.

## Introduction
The creation of a textbook’s index requires the ability to determine the frequency and location of words in a document.
The information is stored in a structure where it lists the distinct words in alphabetical order and makes references to each
line on which the word is used. For instance, consider the text below:

The Hinge tool lets you select a hinged element on your model and move it in the directions indicated by the arrows. A selected
element can be moved using your mouse or the arrow keys on your keyboard. When an element can be rotated in multiple directions,
the selected direction is indicated with a green arrow. To select a different direction, click one of the yellow arrows or use
the TAB key on your keyboard.

The word “element” occurs 3 times in the text and appears on lines 1, 2 and 3. The word “keyboard” occurs 2 times and appears on
lines 3 and 5. Case is not considered. Keyboard and keyboard are the same word. 

There are many words in the textbook that should not be indexed. These are called “Stop Words”. While there are many different wordlists
that can help in filtering common words and phrases, the stop words used in this project will come from the “General Service List”
and is provided (and edited slightly), and named “gsl.txt”. It will not be perfect, but it will do for this project. 

## Application Setup
### The application in command line format, will accept:
1.	Filename of words NOT to be included in the index (the stop words).<br> 
  a.	This file needs to be validated that it is present.<br>
  b.	The filter list will not be in alphabetical order but will be one lower case word per line.<br>
  c.	There will be no punctuation in the file.<br>
2.	Filename of data (text) to be indexed.<br>
  a.	This will need to be validated that it is present as well.<br>
  b.	certain punctuation will need to be removed from the data file<br>
  
### The application, in order, will:
1)	Validate the input files.<br>
2)	Read in the stop words file (gst.txt)<br>
3)	Build a BST of Word(s) to be filtered called “filteredBST”.  Remember this will the list of stop words.<br>
4)	Read in a file containing the data using the second command line variable, while:<br>
  a)	Building a filtered case insensitive BST of Word(s) “indexedBST”<br>
  b)	Storing the line number where the word appears.<br>
  c)	The stored object needs to know how often the word has appeared in the data file.<br>
5)	output the results **(using an overloaded << stream)** of:<br>
  a)	filteredBST in alphabetical order to “filterResults.txt”<br>
  b)	indexedBST in alphabetical order to “indexResults.txt”<br>

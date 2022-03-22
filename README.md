# Command Based Text Editor

## Commands:
While your program is running, it should repeatedly print the contents of the current file, and ask the user what he would like do. The following are the valid commands the user can enter:

### open filename: 
  The program opens the file whose name is provided in the field `filename` and loads its contents.

### save filename: 
  The program writes the contents of the linked list to the file whose name is provided in the `filename` field.

### insert n text: 
  The program inserts a new line in the text at the nth line, which contains the string provided in the field `text`. For example, if the user enters “insert 5 hello my friend”, program inserts a new line at line position 5, and put “hello my friend” in that line. If the file already contains more than n lines, it inserts thin new line between lines n-1 and n, putting the newly inserted text at line n. If the file contains less than n lines, it fills the gap with blank lines until the newly inserted line becomes at position n.

### delete n: 
  The program deletes the line at position n.

### move n m: 
  The program moves the line at position n to position m. replace n text: The program replaces the text inside line n with the string provided in `text`.

### next: 
  Contents of the file should not change, but the program displays the next page.

### prev: 
  Contents of the file should not change, but the program displays the previous page.

### undo: 
  Reverts the last taken action. The user is able to call as many undo commands as he likes, and is able to revert back to the initial state of the file.


# FINAL-PROJECT-STOCK-
  ## Part 1: struct Transaction
  The struct Transaction function is used to define data types, such as: string timestamp; string type; int itemIndex; int quantity.
  ## Part 2: Transaction transactions[MAX_RECORDS] 
  It is used to initialize data.
  ## Part 3: string getTimestamp()
  Provide local time for operations in the program.
  ## Part 4: Function
 1.void loadHistory() function is mainly used to open a txt document to realize long-term data recording. In this function, the If statement is used to judge the conditions (distinguish between restock and sale situations). The while statement is used to run this function for a long time.
2.void saveHistory() function is used to store data in a txt document to realize the recording function.
3.void displayStock() function is used to display the current inventory, and the for loop statement is used to print data.
4.void restockItem() function is used to calculate the purchase quantity and update the purchase quantity, and the If statement is used to determine whether the input data is correct.
5.void sellItem() function is used to calculate the sales quantity and update the sales quantity, and the If statement is used to determine whether the input data is correct.
6.void showTransactions() function is used to display various data that have been recorded (sales history, replenishment history and its time and quantity)
  ## Part 5: main function
 n the main function, I used if-else statements to set up the GUI. The user can use other functions only after entering the correct account name and password. At the same time, I used if-else statements to control the options and provided 6 options (numbers 1-6) for the user to choose the function. I also used a while loop to allow the program to run repeatedly.
  ## Part 6: Exit
  After selecting the exit option, the program saves all data to RecordDate.txt. The next time you reopen the program, the program automatically reads the last recorded data and displays it.

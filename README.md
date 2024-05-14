>Here I have tried implementing an application that allows users to manage shared expenses amongst a group 
 of people. Each user can spend money and share expenses with others. The goal is to calculate the net amount 
 owed or to be paid by each user in the group. 
>The application has been implemented using an array of structures to store user and expense information.

>There are two structures that define a user and an expense made by any user.
>The functions valid_usr_id(int) and valid_exp_id(int) helps to check if the user or the expense reffered is stored in data
 base(or is valid or not) and returns the index where that is stored in the array of structure.
>The functions add_user(int) and add_expense(int) allows to add new user and new expense for any existing user.
 These functions provide sorted insertion of the new entry in the array of structure.
>delete_expense(int) helps in deleting the expense entry.
>view_amount_owed(int) shows the amount that a person owes(from other users) in total.
>view_amount_to_pay(int) shows the amount to be paid to other users in total.
>settle_up(int,int) takes up two user ids and settles all payment that the first user have to make to the other.
>user_balances(int) shows all the amounts to be recieved and given to other users.
>delete_user_id(int) helps to delete a user given all its payments are settled.

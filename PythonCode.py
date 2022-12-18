import re
import string
    
grocery_list = {}

# creates the file in a sorted alphabetical order to make an easier input 

def create_grocery_list():

    grocery_list_f = open('groceries.txt', 'r')
    for line in grocery_list_f.readlines():
        if line.strip() not in grocery_list.keys():
            grocery_list[line.strip()] = 1
        else:
            grocery_list[line.strip()] = (grocery_list[line.strip()] + 1)
    
    alphabet_groceries = []
    for line in grocery_list:
        alphabet_groceries.append(line)
    alphabet_groceries.sort()

    new_file = open('sorted_groceries_and_count.txt', 'w+')

    for line in alphabet_groceries:
        string = line.strip()+":"+str(grocery_list[line])+'\n' 
        new_file.write(string) 
        
    grocery_list_f.close()
    new_file.close()


# print the menu count for each product 
def print_menu_count():
    f = open('sorted_groceries_and_count.txt', 'r')

    for line in f:
        print(line, end = "")

    f.close()

# Helper function for printing the lines in other functions that returns a split list of the value of sells of a product and the product name as tokens

def split_items(string_in):

    f = open('sorted_groceries_and_count.txt', 'r')
    
    for line in f:
        if string_in.lower() in line.lower():
            items = (line.split(':'))
            break
            
    return items    
    f.close()

# uses above helper function to create two lists of word and quantity separately. 
# The quantity position correlates to the word and helps in printing correct amount of * characters

def print_graph():
    
    f = open('sorted_groceries_and_count.txt', 'r')
    l = f.readlines()
    items = []
    
    for string_in in l:
        x = split_items(string_in)
        for xs in x:
            items.append(xs.strip())
    
    word = []
    quantity = []
    x = 0

    for i in items:
        if( x % 2 == 0 ):
            word.append(i)
        else:
            quantity.append(i)
        x = x + 1

    for i in range(len(word)):
        abc = ""
        print(word[i], end = ":")

        for j in range((int)(quantity[i])):
            abc = abc + "*"
        
        # used for formating the histogram to a more visible comparison by setting the formating to an equal distance start
        x = 12 - len(word[i])
        s = "{:<"+str(x)+"}"
        print(s.format(" "),"|",abc, end = "")
        print()

    f.close()

# Get the item count for a certain product using the name and helper function
def get_item_count(string_in):
    items = split_items(string_in)
    return (int)(items[1].strip())



def get_is_valid(string_in):

    f = open('sorted_groceries_and_count.txt', 'r')

    for line in f:
        if string_in.lower() in line.lower():
            return True

    return False

    f.close()
    

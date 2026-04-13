"""Implemntations done in lecture - Python"""

"""Lecture 3, converting from decimal to binary"""
# Converting to decimal is easy enough; all you have to do is 
# multiply each digit by 2^index (0 based index, right->left incrasing)
# The easiest way to convert decimal to binary is dividng
# by 2 and recording remainders until ur final value is 0

#lecture implementaiton:

def get_decimal_digits(d): # split a number into a list
  digits = []
  while d != 0:
    digits = [(d % 10)] + digits #extracts rightmost digit
    d //= 10 #integer division to remove rightmost
  return digits

def get_binary_digits(b): #convert binary->decimal
  digits = []
  while b != 0:
    digits = [(b % 2)] + digits #extract rightmost bit
    b //= 2 #shift right
  return digits

print(get_decimal_digits(521)) #prints [5,2,1]
print(get_binary_digits(25)) #prints [1,1,0,0,1]
#a visual understanding of decimal->binary is:
# d=25 → 25 % 2 = 1 → digits = [1]
# d=12 → 12 % 2 = 0 → digits = [0,1]
# d=6  → 6  % 2 = 0 → digits = [0,0,1]
# d=3  → 3  % 2 = 1 → digits = [1,0,0,1]
# d=1  → 1  % 2 = 1 → digits = [1,1,0,0,1] final answer

"""
Lecture 21: Linked Lists II
"""
# Linked lists part2, implemented in python
class Node:
  def __init__(self, value):
      self.value = value
      self.next = None 
  
  def __str__(self): #builtin func so print becomes easier
      return f"{self.value}"

# to create our linked lists, we can create a series of nodes and link them together:
if __name__ == '__main__':
  n1 = Node(12)
  n2 = Node(15)
  n3 = Node(500)

  n1.next = n2
  n2.next = n3
# etc
# because of how the python memory model works, we have made n1.next and n2 point
# to the same address, making them "the same thing"
#analogous to C as:
""" 
node *n1 = create_node(12); // here create_node preforms memory allocation
node *n2 = create_node(15); 
n1->next = n2;
"""
# an alternative way to make our linkedlists is through classes:
class LinkedList:
  def __init__(self):
      self.head = None
  
  def get_i(self, i):
      # return the value at index i
      cur = self.head
      for j in range(i):
          cur = cur.next
      return cur.value

  def append(self, value):
      '''Add a new node with the value value to the end of the list'''
      # Create a new node
      new_node = Node(value)

      if self.head == None: # if empty, make it head
          self.head = new_node
      else:
          # if non-empty, go to last, insert
          cur = self.head
          while cur.next != None:
              cur = cur.next
          cur.next = new_node
  
  def insert(self, value, i):
      '''Insert a node with the value value at index i'''
      new_node = Node(value)

      if i == 0:
          new_node.next = self.head
          self.head = new_node
      else:
          cur = self.head
          for j in range(i-1):
              cur = cur.next # go to node b4
          new_node.next = cur.next #make the next for our node the next for the node we want to insert after
          # (in other words, previous node's next becomes ours)
          cur.next = new_node # make the node we want to insert after point to our new node
          # (in other words, previous node now points to us)

  def __str__(self):
      cur = self.head
      s = ""
      if(cur == None):
          return "Empty list :("
      
      while cur != None:
          s += str(cur) + " -> "
          cur = cur.next
      return s[:-4] # remove last arrow (space before arrow,arrow 2 times, space after)
    

"""
LECTURE 22: Stacks & Quenes
"""
# A stack can be thought of as a stack of block, you may only access the last block
# it has push() and pop(), pop returns last elemnt
# it is a FILO (first in last out) ds, you to access i, you must remove (use pop) on i-1 elemnts
# unless it is the last one
# however you can insert in o(1) 
#implementation can be done very easily with a list:
class Stack:
    def __init__(self):
        self.data = []
    
    def push(self, item):
        self.data.append(item)
    
    def pop(self):
        return self.data.pop()
# `its very easy because pop (only in the later versions of python)
# acts exactly like a stack pop

# if you wanted to implement it without pythons builtin pop:
class Stack:
    def __init__(self):
        self.data = []
    
    def push(self, item):
        self.data.append(item)
    
    def pop(self):
        # same as self.data.pop()
        ret_val = self.data[-1]
        del self.data[-1]
        return ret_val

# A queue is very similar to a stack, the difference is it is
# FIFO (first in first out), it has operations queue, and dequeue
# you can think of it as literally a queue of ppl, either you join the queue or
# you dequeue (first person dqueues and value is returned)
# this means the only change is from going to last index (-1) to first (0)
#Implementation: 
class Queue:
    def __init__(self):
        self.data = []
    
    def enqueue(self, item):
        self.data.append(item)
    
    def dequeue(self):
        ret_val = self.data[0]
        del self.data[0]
        return ret_val
# here, pop and enqueue are o(1), while dequeue is o(n) since you have to shift every elemnt to previous spot
# a commmon practice, if you were to implement this in c, is to double the allocated memory
# each time you fill space

# We can improve our implementations of queues using linked lists
# the idea is that if we remove the first element, instead of shifting everything,
# we can just change the HEAD pointer of the linked list to direct to the second element, which takes const time
# We can implement this as:
import linkedlist #code from lecture 21

class LLQueue:
    def __init__(self):
        self.data = linkedlist.LinkedList()
    
    def enqueue(self, value):
        def enqueue(self):
        self.data.append(value)
        
    def dequeue(self):
        ret_value = self.data.head.value
        self.data.head = self.data.head.next





 #include "bigInteger.h"
 #include <stdio.h>
 #include <stdlib.h>
 
 struct BigInteger initializeList() 
 {
      struct BigInteger list;
      list.head = NULL;
      return list;
 }
 
 void insertDigit(struct BigInteger list, int digit) 
 {
      struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
      newNode->data = digit;                                                           //used to make a new node
      newNode->next = list.head;
      list.head = newNode;
 }
 
 
 int compareLists(struct BigInteger num1, struct BigInteger num2) 
 {
      struct Node* node1 = num1.head;
      struct Node* node2 = num2.head;
      while (node1 != NULL && node2 != NULL)                //this is used to compare linklist
      {
          if (node1->data > node2->data) 
          {
              return 1;
          } 
          else if (node1->data < node2->data) 
          {
              return -1;
          }
          node1 = node1->next;
          node2 = node2->next;
      }
      if (node1 != NULL) 
      {
          return 1;
      } 
      else if (node2 != NULL) 
      {
          return -1;
      }
      return 0;
 }
 
 void printList(struct BigInteger list) 
 {
      struct Node* current = list.head;
      while (current != NULL) 
      {
           printf("%d", current->data);             //used to display the list
          current = current->next;
      }
      printf("\n");
 }
 struct BigInteger add(struct BigInteger num1, struct BigInteger num2)    //function is used to add biginteger
 {
      struct BigInteger result = initializeList();
      struct Node* node1 = num1.head;
      struct Node* node2 = num2.head;
      int c = 0;
      while (node1 != NULL || node2 != NULL || c != 0) 
      {
          int sum = c;
          if (node1 != NULL) 
          {
              sum += node1->data;
              node1 = node1->next;
          }
          if (node2 != NULL) 
          {
              sum += node2->data;
              node2 = node2->next;
          }
          c = sum / 10;
          sum = sum % 10;
          insertDigit(result, sum);
      }
      if (c > 0) 
      {
          insertDigit(result, c);
      }
      return result;
 }
 
 struct BigInteger reverse(struct BigInteger list) 
 {
      struct Node* prev = NULL;
      struct Node* current = list.head;
      struct Node* next = NULL;
      while (current != NULL) 
      {
          next = current->next;
          current->next = prev;
          prev = current;
          current = next;
      }
      list.head = prev;
      return list;
 }
 
 struct BigInteger sub(struct BigInteger num1, struct BigInteger num2)      //function is used to subtract biginteger
 {
      struct BigInteger result = initializeList();
      struct Node* node1 = num1.head;
      struct Node* node2 = num2.head;
      int c = 0;
  
      while (node1 != NULL || node2 != NULL) 
      {
          int diff = c;   
          if (node1 != NULL) 
          {
              diff += node1->data;
              node1 = node1->next;
          }
          if (node2 != NULL) 
          {
              diff -= node2->data;
              node2 = node2->next;
          }
          if (diff < 0) 
          {
              diff += 10;
              c = -1;
          } 
          else 
          {
              c = 0;
          }
          insertDigit(result, diff);
      }
      while (result.head != NULL && result.head->data == 0) 
      {
          struct Node* temp = result.head;
          result.head = result.head->next;
          free(temp);
      }
      return result;
 }
 
 struct BigInteger mul(struct BigInteger num1, struct BigInteger num2)       //function is used to multiply biginteger
 {
      struct BigInteger result = initializeList();
      struct Node* node1 = num1.head;
      while (node1 != NULL) 
      {
          int c = 0;
          struct BigInteger temp = initializeList();
          struct Node* node2 = num2.head;
          while (node2 != NULL || c != 0) 
          {
              int product = c;
              if (node2 != NULL) 
              {
                  product += node1->data * node2->data;
                  node2 = node2->next;
              }
              c = product / 10;
              product = product % 10;
              insertDigit(temp, product);
          }
          result = add(result, temp);
          freeList(temp);
          node1 = node1->next;
      }
      return reverse(result);
 }
 
 struct BigInteger div1(struct BigInteger num1, struct BigInteger num2)      //function is used to divide biginteger
 {
      struct BigInteger result = initializeList();
      struct BigInteger remainder = initializeList();
      struct Node* current = num1.head;
  
      while (current != NULL) 
      {
          insertDigit(remainder, current->data);
          while (compareLists(remainder, num2) >= 0) 
          {
              struct BigInteger temp = sub(remainder, num2);            
              struct Node* lastDigit = result.head;
              struct Node* prev = NULL;
              while (lastDigit != NULL) 
              {
                  lastDigit->data++;
                  prev = lastDigit;
                  lastDigit = lastDigit->next;
              }            
              if (prev != NULL && prev->data > 9) 
              {
                  prev->data %= 10;
                  insertDigit(result, 1);
              }
              freeList(remainder);
              remainder = temp;
          }
          current = current->next;
      }    
      if (result.head == NULL) 
      {
          insertDigit(result, 0);
      }
      freeList(remainder);
      return result;
 }
 
 struct BigInteger mod(struct BigInteger num1, struct BigInteger num2)      //function is used to mod biginteger
 {
      struct BigInteger remainder = initializeList();
      struct Node* current = num1.head;
      while (current != NULL) 
      {
          insertDigit(remainder, current->data);
          while (compareLists(remainder, num2) >= 0) 
          {
              struct BigInteger temp = sub(remainder, num2);
              freeList(remainder);
              remainder = temp;
          }
          current = current->next;
      }
      return remainder;
 }
 
 void freeList(struct BigInteger list) 
 {
      struct Node* current = list.head;
      while (current != NULL) 
      {
          struct Node* temp = current;
          current = current->next;
          free(temp);
      }
 }
 
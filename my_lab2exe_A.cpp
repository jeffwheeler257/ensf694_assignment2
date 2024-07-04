/*
 *  my_lab2exe_A.cpp
 *  ENSF 694 Lab 2 - Exercise A
 *  Created by Mahmood Moussavi
 *  Completed by: Jeff Wheeler
 *  Submission date: July 10, 2024
 */

int my_strlen(const char *s);
/*  Duplicates strlen from <cstring>, except return type is int.
 *  REQUIRES
 *     s points to the beginning of a string.
 *  PROMISES
 *     Returns the number of chars in the string, not including the
 *     terminating null.
 */

void my_strncat(char *dest, const char *source, int n);
/*  Duplicates strncat from <cstring>, except return type is void.
 *  REQUIRES
 *      dest and source point to the beginning of a string 
 *      n > 0
 *  PROMISES
 *      Returns the concatenation of dest and n number of characters 
 *      from source.
 */

#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
    char str1[7] = "banana";
    const char str2[] = "-tacit";
    const char* str3 = "-toe";
    
    /* point 1 */
    char str5[] = "ticket";
    char my_string[100]="";
    int bytes;
    int length;
    
    /* using strlen library function */
    length = (int) my_strlen(my_string);
    cout << "\nLine 1: my_string length is " << length;
  
    /* using sizeof operator */
    bytes = sizeof (my_string);
    cout << "\nLine 2: my_string size is " << bytes << " bytes.";
   
    /* using strcpy library function */
    strcpy(my_string, str1);
    cout << "\nLine 3: my_string contains: " << my_string;
   
    length = (int) my_strlen(my_string);
    cout << "\nLine 4: my_string length is " << length << ".";
   
    my_string[0] = '\0';
    cout << "\nLine 5: my_string contains:\"" << my_string << "\"";
  
    length = (int) my_strlen(my_string);
    cout << "\nLine 6: my_string length is " <<  length << ".";
   
    bytes = sizeof (my_string);
    cout << "\nLine 7: my_string size is still " << bytes << " bytes.";
 
    /* strncat append the first 3 characters of str5 to the end of my_string */
    my_strncat(my_string, str5, 3);
    cout << "\nLine 8: my_string contains:\"" << my_string << "\"";
  
    length = (int) my_strlen(my_string);
    cout << "\nLine 9: my_string length is " << length << ".";
   
    my_strncat(my_string, str2,  4);
    cout << "\nLine 10: my_string contains:\"" << my_string << "\"";
    
    /* strncat append ONLY up to '\0' character from str3 -- not 6 characters */
    my_strncat(my_string, str3, 6);
    cout << "\nLine 11: my_string contains:\"" << my_string << "\"";
   
    length = (int) my_strlen(my_string);
    cout << "\nLine 12; my_string has " << length << " characters.";

    cout << "\n\nUsing strcmp - C library function: ";
    
    cout << "\n\"ABCD\" is less than \"ABCDE\" ... strcmp returns: " <<
    strcmp("ABCD", "ABCDE");

    cout << "\n\"ABCD\" is less than \"ABND\" ... strcmp returns: " <<
    strcmp("ABCD", "ABND");
    
    cout << "\n\"ABCD\" is equal than \"ABCD\" ... strcmp returns: " <<
    strcmp("ABCD", "ABCD");
 
    cout << "\n\"ABCD\" is less than \"ABCd\" ... strcmp returns: " <<
    strcmp("ABCD", "ABCd");

    cout << "\n\"Orange\" is greater than \"Apple\" ... strcmp returns: " <<
    strcmp("Orange", "Apple") << endl;
    return 0;
}

int my_strlen(const char *s){
    int length = 0;
    while (*s){
        s = s + 1;
        length++;
    }
    return length;
}

void my_strncat(char *dest, const char *source, int n){
    int str_dest_len = 0;
    while (*dest){
        dest = dest + 1;
        str_dest_len++;
    }

    dest = dest - str_dest_len; //Is there a better way to iterate through without resetting the pointer to the first address??

    int i;
    for (i = 0; i < n; i++){
        dest[str_dest_len + i] = source[i];
    }
    dest[str_dest_len + i] = '\0';
}
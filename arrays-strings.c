#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
 * Checks if a string is a palindrome
 */
bool isPalindrome(char str[]) {
    int b = strlen(str) - 1;
    int a = 0;

    // compare each char from the front and end of the string with the other, working inward
    while(b > a) {
        // if the chars dont match, not a palindrome
        if(str[a++] != str[b--]) {
            printf("%s is not a palindrome\n", str);
            return false;
        }
    }

    printf("%s is a palindrome\n", str);
    return true;
}


/*
 * Reverses a string
 */
void reverseStr(char* str) {
    int b = strlen(str) - 1;
    int a = 0;
    char temp;

    // swap each char from the front and end of the string with each other, working inward
    while(b > a) {
        temp = str[a];
        str[a] = str[b];
        str[b] = temp;
        b--;
        a++;
    }
}


/*
 * Check if 2 strings are anagrams of each other
 */
int isAnagram(char* str1, char* str2) {
    int countArr[26] = {0};
    int countNum = 0;

    for(char* s = str1; *s != '\0'; s++) {
        countArr[*s - 'a']++;
    }

    for(char* s = str2; *s != '\0'; s++) {
        countArr[*s - 'a']--;
    }

    for(int i = 0; i < sizeof(countArr)/sizeof(countArr[0]); i++) {
        countNum += abs(countArr[i]);
    }

    return (countNum == 0) ? 1 : 0;
}


/*
 * Given array of consecutive ints, finds missing number
 */
int consecutiveInts(int nums[], int size) {
    // walk through array
    for(int i = 0; i < size; i++) {
        if(nums[i] != (i + nums[0])) {
            return i + nums[0];
        }
    }

    return -1;
}


/*
 * Given array of n-1 numbers from 1 to n, find missing num
 */
int missingNum(int arr[], int n) {
    // use sum formula
    int sum = (n+1)*(n+2)/2;

    // subtract each array element from sum
    for(int i = 0; i < n; i++) {
        sum -= arr[i];
    }

    // remaining value is the missing num
    return sum;
}


/*
 * Given array of numbers, rotate right by n
 */
void rightRotate(int arr[], int d, int len) {
    int idxNew;
    int arrNew[len];

    // find the new index of each array element
    for(int i = 0; i < len; i++) {
        // if new index is outside of array size, move to front of array
        if((i+d) > len-1) {
            idxNew = (i+d) - len;
        } else {
            idxNew = i+d;
        }
        
        arrNew[idxNew] = arr[i];
    }

    // move the new shifted array elements to the original array
    for(int i = 0; i < len; i++) {
        arr[i] = arrNew[i];
    }
}


int main() {
    char str1[] = "ABBA";
    char str2[] = "APPLE";

    isPalindrome(str1);
    isPalindrome(str2);
    reverseStr(str2);

    printf("APPLE reversed: %s\n", str2);

    int arrInts[] = {1, 2, 3, 4, 6, 7, 8, 9};
    int missing = consecutiveInts(arrInts, sizeof(arrInts)/sizeof(arrInts[0]));

    printf("consecutiveInts() = %d\n", missing);

    int missing2 = missingNum(arrInts, sizeof(arrInts)/sizeof(arrInts[0]));
    printf("missingNum() = %d\n", missing2);

    rightRotate(arrInts, 2, sizeof(arrInts)/sizeof(arrInts[0]));
    for(int i = 0; i < sizeof(arrInts)/sizeof(arrInts[0]); i++) {
        printf("%d ", arrInts[i]);
    }
    printf("\n");

    char anagram1[] = "abcdefg";
    char anagram2[] = "defbcgahi";
    int anagramResult = isAnagram(anagram1, anagram2);
    printf("Is anagram?: %d\n", anagramResult);


}

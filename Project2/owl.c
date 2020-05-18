//
//Ordered Word Ladder
//
// Authors:
// Chongshi Wang
//

#include "Graph.h"
#include "Quack.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @param  the first word
 * @param  the second word
 * @return true or false
 * @function : judge whether two words satisfy one of two conditions of requirement
 */

bool differByOne(char *firstWord, char *secondWord) {
    // get the length of two words
    int length1 = strlen(firstWord);
    int length2 = strlen(secondWord);
    // if: the length of two words is same
    if (length1 == length2) {
        int count = 0;
        // count the number of elements of two words which are different in the same position
        for (int i = 0; i < length1; i++) {
            if (*(firstWord + i) != *(secondWord + i))
                count++;
        }
        // count == 1: satisfy changing one letter
        if (count == 1) {
            return true;
        }
        return false;
    } else if (length1 > length2) {
        // if the length of first word - second word == 1
        if (length1 - length2 == 1) {
            // if two words start with different letter：
            // this condition is satisfied only if the remaining letters of long words are the same as
            // that of short words in the same position
            if (*firstWord != *secondWord) {
                firstWord++;
                // if there are different letters in the same position: return false
                for (int i = 0; i < length2; i++) {
                    if (*(firstWord + i) != *(secondWord + i)) {
                        return false;
                    }
                }
                return true;
            } else {
                // if the first letter of two words is the same
                // special case: the length of short words is one
                if (length2 == 1) {
                    return true;
                }
                // count the number of same letters of two words in the same position
                int sameWord = 0;
                for (int i = 0; i < length2; i++) {
                    // the letter of long words in the current position is different from the short words
                    if (*firstWord != *secondWord) {
                        // the letter in the next position of long words is the same as
                        // the letter of short words in current position
                        if (*(firstWord + 1) == *(secondWord)) {
                            firstWord++;
                            while (*firstWord != '\0') {
                                // if there are different letters in the same position
                                // after changing the position of long words: false
                                if (*firstWord != *secondWord) {
                                    return false;
                                }
                                firstWord++;
                                secondWord++;
                            }
                            return true;
                        }
                        return false;
                    }
                        // count the number of same letters of two words in the same position
                    else {
                        sameWord++;
                    }
                    firstWord++;
                    secondWord++;
                }
                // if the number of same letters is equal to the length of short words:
                // the extra one letter of long words is inserted at the end of the short words
                // satisfy the requirement
                if (sameWord == length2) {
                    return true;
                } else {
                    return false;
                }
            }
        } else { // length1 - length2 > 1
            return false;
        }
    } else {
        // if the length of second word - first word == 1
        // the method of this is the same as the above(length1 - length2 == 1)
        if (length2 - length1 == 1) {
            if (*firstWord != *secondWord) {
                secondWord++;
                for (int i = 0; i < length1; i++) {
                    if (*(firstWord + i) != *(secondWord + i)) {
                        return false;
                    }
                }
                return true;
            } else {
                if (length1 == 1) {
                    return true;
                }
                int sameWord = 0;
                for (int i = 0; i < length1; i++) {
                    if (*firstWord != *secondWord) {
                        if (*(firstWord) == *(secondWord + 1)) {
                            secondWord++;
                            while (*firstWord != '\0') {
                                if (*firstWord != *secondWord) {
                                    return false;
                                }
                                firstWord++;
                                secondWord++;
                            }
                            return true;
                        }
                        return false;
                    } else {
                        sameWord++;
                    }
                    firstWord++;
                    secondWord++;
                }
                if (sameWord == length1) {
                    return true;
                } else {
                    return false;
                }
            }
        } else { // length2 - length1 > 1
            return false;
        }
    }
}

/**
 * @param  the graph
 * @param  the number of words
 * @param  the array of words
 * @function : graph is set up according to the requirement
 */

void createGraph(Graph graph, int numberOfWords, char words[1000][21]) {
    //two 'for' loops traverse the array
    for (int i = 0; i < numberOfWords; i++) {
        char *str1 = words[i];
        for (int j = i + 1; j < numberOfWords; j++) {
            char *str2 = words[j];
            // if: different words of array meet differByOne function
            if (differByOne(str1, str2)) {
                // create two edges and insert them into the graph
                Edge edge1 = newEdge(i, j);
                insertEdge(edge1, graph);
                Edge edge2 = newEdge(j, i);
                insertEdge(edge2, graph);
            }
        }
    }
}

/**
 * @param  the original quack
 * @param  the copy version of the original quack
 * @function : copy one Quack data to another Quack
 */

void copyQuack(Quack quackOrig, Quack quackCopy) {
    int value = pop(quackOrig);
    // extract the last data of the original quack
    int valueEnd = value;
    qush(value, quackOrig);
    push(value, quackCopy);
    value = pop(quackOrig);
    // while: pop the data from the original quack
    // qush this data into the copy version
    while (valueEnd != value) {
        qush(value, quackOrig);
        qush(value, quackCopy);
        value = pop(quackOrig);
    }
    // push the last data into the original quack
    push(value, quackOrig);
}

/**
 * @param  the quack
 * @param  the counts of quack
 * @param  the array of words
 * @param  the longest length
 * @function : print the final result
 */
// 用queue 就行
void printQuackWithWords(Quack *quack, int quackCount, char words[1000][21], int maxLength) {
    printf("Longest ladder length: %d\n", maxLength);
    printf("Longest ladders:\n");
    int index = 1;
    // it prints only 99 paths if finding more than 100 paths
    for (int i = 0; i < quackCount && index < 100; i++) {
        if (index < 10) {
            printf(" %d:", index++);
        } else {
            printf("%d:", index++);
        }
        // judge whether it is the last data in the quack
        while (!isEmptyQuack(quack[i])) {
            int v = pop(quack[i]);
            if (isEmptyQuack(quack[i])) {
                printf(" %s", words[v]);
            } else {
                printf(" %s ->", words[v]);
            }
        }
        printf("\n");
    }
}

/**
 * @param  the graph
 * @param  the number of words
 * @param  the quack
 * @param  the root of graph
 * @param  the temporary quack
 * @param  the counts of quack
 * @param  the counts of length
 * @param  the longest length
 * @function : find the longest length
 */
// findLength(graph, numberOfWords, quack, i, q1(root), &quackCount, 1, &maxLength);
void findLength(Graph graph, int numberOfWords, Quack *quack, int beginPos, Quack q1, int *quackCount, int length,
                int *maxLength) {
    bool beLast = true;
    int j;
    // search leaf nodes from the root in the graph
    for (j = beginPos + 1; j < numberOfWords; j++) {
        Edge e = newEdge(beginPos, j);
        // if an edge exists: search recursively
        if (isEdge(e, graph) && beginPos < j) {
            beLast = false;
            Quack quackTemp = createQuack();
            copyQuack(q1, quackTemp);
            // save the previous data and wait for the next recursion
            qush(j, quackTemp);
            findLength(graph, numberOfWords, quack, j, quackTemp, quackCount, 1 + length, maxLength);
            destroyQuack(quackTemp);
        }
    }
    // if it is the bottom leaf node
    if (beLast) {
        // if length > longest length: clear the previous path
        if (length > *maxLength) {
            int i = 0;
            for (i = 0; i < *quackCount; i++) {
                makeEmptyQuack(quack[i]);
            }
            *quackCount = 1;
            int index = 0;
            copyQuack(q1, quack[index]);
            *maxLength = length;
        } else if (length == *maxLength) {
            // if length == longest length: store the path into the quack
            int index = *quackCount;
            copyQuack(q1, quack[index]);
            // number of possible ways + 1
            *quackCount = (*quackCount) + 1;
        }
    }
}

/**
* @ the main function
*/

int main() {
    int input;
    // record the index for each word
    int wordIndex = 0;
    // count the number of words
    int numberOfWords = 0;
    // two-dimensional array records all the input words
    char words[1000][21];
    // array records the each input word
    char word[21];
    // getchar: operate on every input
    while ((input = getchar()) != EOF) {
        // if: the input is not the letter
        if (!isalpha(input)) {
            if (strlen(word) > 0) {
                if (numberOfWords > 0) {
                    // remove adjacent duplicate words
                    if (strcmp(words[numberOfWords - 1], word) != 0) {
                        strcpy(words[numberOfWords], word);
                    } else {
                        numberOfWords--;
                    }
                } else {
                    // the number of words == 0
                    strcpy(words[numberOfWords], word);
                }
                numberOfWords++;
            }
            wordIndex = 0;
            word[wordIndex] = '\0';
            continue;
        }
        // the input is letter
        word[wordIndex] = input;
        wordIndex++;
        word[wordIndex] = '\0';
    }
    // if no word is entered
    if (numberOfWords == 0) {
        return 1;
    }
    printf("Dictionary\n");
    for (int i = 0; i < numberOfWords; i++) {
        printf("%d: %s\n", i, words[i]);
    }
    printf("Ordered Word Ladder Graph\n");
    // create graph and print graph
    Graph graph = newGraph(numberOfWords);
    createGraph(graph, numberOfWords, words);
    showGraph(graph);
    // create quack
    Quack quack[10000];
    for (int i = 0; i < 10000; i++) {
        quack[i] = createQuack();
    }
    // the loop recursively traverses
    int quackCount = 0;
    int maxLength = 0;
    // find the root of graph
    for (int i = 0; i < numberOfWords; i++) {
        int beTop = 1;
        for (int j = 0; j < i; j++) {
            Edge e = newEdge(i, j);
            if (isEdge(e, graph)) {
                beTop = 0;
            }
        }
        if (beTop) {
            // the temporary quack stores the data that has been found
            Quack quackTemp = createQuack();
            qush(i, quackTemp);
            // start at the root node and search the longest path
            findLength(graph, numberOfWords, quack, i, quackTemp, &quackCount, 1, &maxLength);
            destroyQuack(quackTemp);
        }
    }
    printQuackWithWords(quack, quackCount, words, maxLength);
    // free quack
    for (int i = 0; i < 10000; i++) {
        quack[i] = destroyQuack(quack[i]);
    }
    return 0;
}

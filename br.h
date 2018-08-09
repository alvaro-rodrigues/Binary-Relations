#ifndef BR_H
#define BR_H

typedef struct node {
  int index;
  int x;
  int y;
  struct node *next;
} node_t;

typedef struct {
  int num_elements;
  node_t *first;
  node_t *last;
} list_t;

list_t *create_list();
void add_elementFinal(list_t *list, int x, int y);
void sortAdd(list_t **sortedList, node_t *toAdd);
void sortList(list_t **list);
void removeDuplicates(list_t *list);
char isReflective(list_t *list, int array[], int n, list_t *reflectiveClosure, list_t *reflectiveLack);
char isNotReflective(list_t *list, int array[], int n, list_t *notReflectiveLack);
char isSymmetric(list_t *list, list_t *symmetricClosure, list_t *symmetricLack);
char isAntiSymmetric(list_t *list, list_t *antiSymmetricLack);
char isTransitive(list_t *list, list_t *transitiveClosure, list_t *transitiveLack);
void removeElement(list_t *list, int x, int y);
void printList(list_t *list);
void printAntiSymmetric(list_t *antiSymmetricLack);
void printClosure(list_t *list);

#endif
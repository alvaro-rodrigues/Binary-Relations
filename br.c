#include <stdio.h>
#include <stdlib.h>
#include "br.h"

list_t *create_list() {
  list_t *list = (list_t *) malloc(sizeof(list_t));
  if (list == NULL) {
    printf("Error,  sem memória!!");
    exit(1);
  }
  list->first = NULL;
  list->last = NULL;
  list->num_elements = 0;
  return list;
}

void addElementFinal(list_t *list, int x, int y) {
  node_t *node = (node_t *) malloc (sizeof(node_t));
  node->x = x;
  node->y = y;
  node->index = list->num_elements;
  node->next = NULL;

  if (list->last != NULL)
    list->last->next = node;

  list->last = node;
  list->num_elements++;
  if (list->first == NULL)
    list->first = node;
}


void sortAdd(list_t **sortedList, node_t *toAdd) {
  node_t *toVisit;
  if ((*sortedList)->first == NULL || ((*sortedList)->first->x > toAdd->x || ((*sortedList)->first->x >= toAdd->x && (*sortedList)->first->y >= toAdd->y))) {
      toAdd->next = (*sortedList)->first;
      (*sortedList)->first = toAdd;
  }
  else {
    toVisit = (*sortedList)->first;
    while (toVisit->next != NULL && (toVisit->next->x < toAdd->x || (toVisit->next->x <= toAdd->x && toVisit->next->y < toAdd->y))) {
      toVisit = toVisit->next;
    }
    toAdd->next = toVisit->next;
    toVisit->next = toAdd;
  }
}

void sortList(list_t **list) {
  list_t *sortedList = create_list();
  node_t *toVisit = (*list)->first;
  while (toVisit != NULL) {
    node_t *next = toVisit->next;
    sortAdd(&sortedList, toVisit);
    toVisit = next;
  }
  (*list)->first = sortedList->first;
}

void removeDuplicates(list_t *list) {
  node_t *toUse, *toFind, *duplicate;
  toUse = list->first;
  while (toUse != NULL && toUse->next != NULL) {
    toFind = toUse;
    while (toFind->next != NULL) {
      if (toUse->x == toFind->next->x && toUse->y == toFind->next->y)
      {
        duplicate = toFind->next;
        toFind->next = toFind->next->next;
        free(duplicate);
      }
      else {
        toFind = toFind->next;
      }
    }
    toUse = toUse->next;
  }
}

char isReflective(list_t *list, int array[], int n, list_t *reflectiveClosure, list_t *reflectiveLack) {
  node_t *toFind;
  char toReturn = 'V';
  int i;
  for(i = 0; i < n; i++) {
    toFind = list->first;
    while (toFind != NULL) {
      if (toFind->x == array[i] && toFind->y == array[i]) {
        add_elementFinal(reflectiveClosure, array[i], array[i]);
        break;
      }
      toFind = toFind->next;
    }
    if (toFind == NULL) {
      toReturn = 'F';
      add_elementFinal(reflectiveClosure, array[i], array[i]);
      add_elementFinal(reflectiveLack, array[i], array[i]);
    }
  }
  return toReturn;
}

char isNotReflective(list_t *list, int array[], int n, list_t *notReflectiveLack) {
  node_t *toFind;
  char toReturn = 'V';
  int i;
  for(i = 0; i < n; i++) {
    toFind = list->first;
    while (toFind != NULL) {
      if (toFind->x == array[i] && toFind->y == array[i]) {
        toReturn = 'F';
        add_elementFinal(notReflectiveLack, array[i], array[i]);
      }
      toFind = toFind->next;
    }
  }
  return toReturn;
}

char isSymmetric(list_t *list, list_t *symmetricClosure, list_t *symmetricLack) {
  node_t *toUse, *toFind;
  char toReturn = 'V';
  int count = 0;
  while (count < list->num_elements) {
    toUse = list->first;
    while (toUse != NULL) {
      if (toUse->index == count) {
        break;
      }
      toUse = toUse->next;
    }
    toFind = list->first;
    while (toFind != NULL) {
      if (toFind->x == toUse->y && toFind->y == toUse->x) {
        break;
      }
      toFind = toFind->next;
    }
    if (toFind == NULL) {
      toReturn = 'F';
      add_elementFinal(symmetricClosure, toUse->y, toUse->x);
      add_elementFinal(symmetricLack, toUse->y, toUse->x);
    }
    count++;
  }
  return toReturn;
}

char isAntiSymmetric(list_t *list, list_t *antiSymmetricLack) {
  node_t *toUse, *toFind;
  char toReturn = 'V';
  int count = 0;
  while (count < list->num_elements) {
    toUse = list->first;
    while (toUse != NULL) {
      if (toUse->index == count) {
        break;
      }
      toUse = toUse->next;
    }
    toFind = list->first;
    while (toFind != NULL) {
      if (toFind->x == toUse->y && toFind->y == toUse->x && toFind->x != toFind->y) {
        toReturn = 'F';
        add_elementFinal(antiSymmetricLack, toUse->y, toUse->x);
      }
      toFind = toFind->next;
    }
    count++;
  }
  sortList(&antiSymmetricLack);
  return toReturn;
}

char isTransitive(list_t *list, list_t *transitiveClosure, list_t *transitiveLack) {
  node_t *toStart, *toUse, *toFind;
  char toReturn = 'V';
  int count = 0;
  while (count < list->num_elements) {
    toStart = list->first;
    while (toStart != NULL) {
      if (toStart->index == count) {
        break;
      }
      toStart = toStart->next;
    }
    toUse = list->first;
    while (toUse != NULL) {
      if (toUse->x == toStart->y) {
        toFind = list->first;
        while (toFind != NULL) {
          if (toFind->x == toStart->x && toFind->y == toUse->y) {
            break;
          }
          toFind = toFind->next;
        }
        if (toFind == NULL) {
          toReturn = 'F';
          add_elementFinal(transitiveClosure, toStart->x, toUse->y);
          add_elementFinal(transitiveLack, toStart->x, toUse->y);
        }
      }
      toUse = toUse->next;
   }
   count++;
  }
  list_t *discard = create_list();
  char aux = toReturn;
  while (aux == 'F') {
    aux = isTransitive(transitiveClosure, transitiveClosure, discard);
  }
  free(discard);
  return toReturn;
}

void removeElement(list_t *list, int x, int y) {
  node_t *toFree = list->first;
  node_t *prev = NULL;
  while (toFree != NULL) {
    if (toFree->x == x && toFree->x == x) {
      break;
    }
    prev = toFree;
    toFree = toFree->next;
  }
  if (toFree == NULL) return;
  if (toFree == list->first) {
    list->first = toFree->next;
  }
  if (toFree == list->last) {
    list->last = prev;
  }
  if (prev != NULL) {
    prev->next = toFree->next;
  }
  free(toFree);
}

void printList(list_t *list) {
  node_t *toVisit = list->first;
  while (toVisit != NULL) {
    printf("(%d,%d); ", toVisit->x, toVisit->y);
    toVisit = toVisit->next;
  }
  printf("\n");
}

void printAntiSymmetric(list_t *antiSymmetricLack) {
  list_t *aux = create_list();
  aux->first = antiSymmetricLack->first;
  node_t *toVisit = aux->first;
  while (toVisit != NULL) {
    printf("(%d,%d) e (%d,%d); ", toVisit->x, toVisit->y, toVisit->y, toVisit->x);
    removeElement(aux, toVisit->y, toVisit->x);
    toVisit = toVisit->next;
  }
  printf("\n");
}

void printClosure(list_t *list) {
  node_t *toVisit = list->first;
  printf("{");
  while (toVisit != NULL) {
    printf("(%d,%d)", toVisit->x, toVisit->y);
    if (toVisit->next != NULL) {
      printf(",");
    }
    toVisit = toVisit->next;
  }
  printf("}");
  printf("\n");
}


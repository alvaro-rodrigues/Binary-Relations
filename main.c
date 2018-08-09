#include <stdio.h>
#include <stdlib.h>
#include "br.h"


int main(int argc, char const *argv[]) {
	
  list_t *list = create_list();
  list_t *reflectiveClosure = create_list();
  list_t *reflectiveLack = create_list();
  list_t *notReflectiveLack = create_list();
  list_t *symmetricClosure = create_list();
  list_t *symmetricLack = create_list();
  list_t *antiSymmetricLack = create_list();
  list_t *transitiveClosure = create_list();
  list_t *transitiveLack = create_list();
  char R, NR, S, AS, T, notSymmetric, equivalenceRelation, partialRelation;
  int n, x, y, i;
	scanf("%d", &n);
  int array[n];
	for (i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}
	while(scanf("%d %d", &x, &y) != EOF)
	{
    add_elementFinal(list, x, y);
    add_elementFinal(symmetricClosure, x, y);
    add_elementFinal(transitiveClosure, x, y);
	}
  sortList(&list);
  printf("1. Reflexiva: %c\n", R = isReflective(list, array, n, reflectiveClosure, reflectiveLack));
  if (reflectiveLack->first != NULL) {printList(reflectiveLack);}
  printf("2. Irreflexiva: %c\n", NR = isNotReflective(list, array, n, notReflectiveLack));
  if (notReflectiveLack->first != NULL) {printList(notReflectiveLack);}
  printf("3. Simetrica: %c\n", S = isSymmetric(list, symmetricClosure, symmetricLack));
  sortList(&symmetricLack);
  if (symmetricLack->first != NULL) {printList(symmetricLack);}
  printf("4. Anti-simetrica: %c\n", AS = isAntiSymmetric(list, antiSymmetricLack));
  if (antiSymmetricLack->first != NULL) {printAntiSymmetric(antiSymmetricLack);}
  if (NR == 'V' && AS == 'V') {
    notSymmetric = 'V';
  } else {
    notSymmetric = 'F';
  }
  printf("5. Assimetrica: %c\n", notSymmetric);
  printf("6. Transitiva: %c\n", T = isTransitive(list, transitiveClosure, transitiveLack));
  removeDuplicates(transitiveLack);
  sortList(&transitiveLack);
  if (transitiveLack->first != NULL) {printList(transitiveLack);}
  printf("\n");
  if (R == 'V' && S == 'V' && T == 'V') {
    equivalenceRelation = 'V';
  } else {
    equivalenceRelation = 'F';
  }
  printf("Relação de equivalencia: %c\n", equivalenceRelation);
  if (R == 'V' && AS == 'V' && T == 'V') {
    partialRelation = 'V';
  } else {
    partialRelation = 'F';
  }
  printf("Relação de ordem parcial: %c\n\n", partialRelation);
  printf("Fecho reflexivo da relação = ");
  printClosure(reflectiveClosure);
  printf("Fecho simetrico da relação = ");
  sortList(&symmetricClosure);
  printClosure(symmetricClosure);
  printf("Fecho transitivo da relação = ");
  removeDuplicates(transitiveClosure);
  sortList(&transitiveClosure);
  printClosure(transitiveClosure);

  return 0;
}
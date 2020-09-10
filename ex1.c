#include <stdio.h>
#include <stdlib.h>
#define C 7
#define K1 5
#define K2 2

typedef struct tree {
	int turn;
	int blackCubes;
	int greenCubes;
	int value;
	struct node *blackSelection1;
	struct node *blackSelectionK1;
	struct node *greenSelection1;
	struct node *greenSelectionK2;
} node;


void insert(node *tree) {
	node *curr, *curr2;
	
	if ((*tree).greenCubes - 1 >= 0) {
		(*tree).greenSelection1 = malloc(sizeof(node));
		curr = (*tree).greenSelection1;
		(*curr).greenCubes = (*tree).greenCubes - 1;
		(*curr).blackCubes = (*tree).blackCubes;
		(*curr).turn = -(*tree).turn;
		insert(&(*curr));	
	}
	if ((*tree).greenCubes - K2 >= 0) {
		(*tree).greenSelectionK2 = malloc(sizeof(node));
		curr = (*tree).greenSelectionK2;
		(*curr).greenCubes = (*tree).greenCubes - K2;
		(*curr).blackCubes = (*tree).blackCubes;
		(*curr).turn = -(*tree).turn;
		insert(&(*curr));
	}
	if ((*tree).blackCubes - 1 >= 0) {
		(*tree).blackSelection1 = malloc(sizeof(node));
		curr = (*tree).blackSelection1;
		(*curr).blackCubes = (*tree).blackCubes - 1;
		(*curr).greenCubes = (*tree).greenCubes;
		(*curr).turn = -(*tree).turn;
		insert(&(*curr));
	}

	if ((*tree).blackCubes - K1 >= 0) {
		(*tree).blackSelectionK1 = malloc(sizeof(node));
		curr = (*tree).blackSelectionK1;
		(*curr).blackCubes = (*tree).blackCubes - K1;
		(*curr).greenCubes = (*tree).greenCubes;
		(*curr).turn = -(*tree).turn;
		insert(&(*curr));
	}
	
	if ((*tree).blackCubes + (*tree).greenCubes == 0) {
		(*tree).value = -(*tree).turn;
		return;		
	} else if ((*tree).turn > 0 ) {
		(*tree).value = -1;
		if ((*tree).greenSelection1 != NULL) {
			curr = (*tree).greenSelection1;
			if ((*curr).value > (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}
		}
		if ((*tree).greenSelectionK2 != NULL) {
			curr = (*tree).greenSelectionK2;
			if ((*curr).value > (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}
		} 
		if ((*tree).blackSelection1 != NULL) {
			curr = (*tree).blackSelection1;
			if ((*curr).value > (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}
		} 
		if ((*tree).blackSelectionK1 != NULL) {
			curr = (*tree).blackSelectionK1;
			if ((*curr).value > (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}
		}
	} else if ((*tree).turn < 0) {
		(*tree).value = 1;
		if ((*tree).greenSelection1 != NULL) {
			curr = (*tree).greenSelection1;
			if ((*curr).value < (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}
		}
		if ((*tree).greenSelectionK2 != NULL) {
			curr = (*tree).greenSelectionK2;
			if ((*curr).value < (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}
		}
		 if ((*tree).blackSelection1 != NULL) {
			curr = (*tree).blackSelection1;
			if ((*curr).value < (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}
		} 
		if ((*tree).blackSelectionK1 != NULL) {
			curr = (*tree).blackSelectionK1;
			if ((*curr).value < (*tree).value) {
				(*tree).value = (*curr).value;
				return;
			}	
		}
	}
	
	return;
} 

void humanPlayer(node *root) {
	
	int grab, backUpGreenCubes, backUpBlackCubes;
	char str;
	
	while (1 == 1) {
		printf("put 'g' or 'G' for greenCubes ang 'b' or 'B' for blackCubes\n");
		scanf("%c", &str);
		
		
		if (str ==  'b' || str == 'B' ) {
		printf("how many from %clack cubes you want \n", str);
		scanf("%d", &grab);
			if (grab == 1 || grab == K1) {
				if ((*root).blackCubes - grab >= 0) {
					(*root).blackCubes = (*root).blackCubes - grab;
					break;
				} else {
					printf("Dwste ksana ton ari8mo den exoun apomeinei %dreen mpales\n", grab);
				}
			}
		} else if (str == 'g' || str == 'G' ) {
			printf("how many from %creen cubes you want \n", str);
			scanf("%d", &grab);
			if (grab == 1 || grab == K2) {
				if ((*root).greenCubes - grab >= 0) {
					(*root).greenCubes = (*root).greenCubes - grab;
					break;
				} else {
					printf("Dwste ksana ton ari8mo den exoun apomeinei %dreen mpales\n", grab);
				}
			}
		}
	}
	backUpGreenCubes = (*root).greenCubes;
	backUpBlackCubes = (*root).blackCubes;
	(*root).blackSelection1 = (*root).blackSelectionK1 = (*root).greenSelection1 = (*root).greenSelectionK2 = NULL;
	(*root).greenCubes = backUpGreenCubes;
	(*root).blackCubes = backUpBlackCubes;

}


void computerPlayer(node *root) {
	node * curr3;
	int backUpGreenCubes, backUpBlackCubes;
	int flag = 0;

	insert(&(*root));
	printf("BlackCubes --%d\nGreenCubes --%d\n", (*root).blackCubes, (*root).greenCubes);

	flag = 0;
 	if ((*root).blackSelectionK1 != NULL && flag == 0) {
		curr3 = (*root).blackSelectionK1;
		if ((*curr3).value > 0) {
			backUpGreenCubes = (*curr3).greenCubes;
			backUpBlackCubes = (*curr3).blackCubes;
			flag = 1;
		}
	}
	if ((*root).greenSelectionK2 != NULL && flag == 0) {
		curr3 = (*root).greenSelectionK2;
		if ((*curr3).value > 0) {
			backUpGreenCubes = (*curr3).greenCubes;
			backUpBlackCubes = (*curr3).blackCubes;
			flag = 1;
		}
	}
	if ((*root).blackSelection1 != NULL && flag == 0) {
		curr3 = (*root).blackSelection1;
		if ((*curr3).value > 0) {
			backUpGreenCubes = (*curr3).greenCubes;
			backUpBlackCubes = (*curr3).blackCubes;
			flag = 1;
		}	
	} 
	if ((*root).greenSelection1 != NULL && flag == 0) {
		curr3 = (*root).greenSelection1;
		if ((*curr3).value > 0) {
			backUpGreenCubes = (*curr3).greenCubes;
			backUpBlackCubes = (*curr3).blackCubes;
			flag = 1;
		}
	} 
	 if (flag == 0){
			printf("8a xasw");
			backUpGreenCubes = (*curr3).greenCubes;
			backUpBlackCubes = (*curr3).blackCubes;
	}
	
	(*root).blackSelection1 = (*root).blackSelectionK1 = (*root).greenSelection1 = (*root).greenSelectionK2 = NULL;
	(*root).greenCubes = backUpGreenCubes;
	(*root).blackCubes = backUpBlackCubes;
	
	printf("%dBlack - %dGreen\n", (*root).blackCubes, (*root).greenCubes);	
}


void main () {

	node *root = NULL;	
	
	root = malloc(sizeof(node));
	(*root).greenCubes = (*root).blackCubes = C;
	(*root).greenSelection1 = (*root).greenSelectionK2 = (*root).blackSelection1 = (*root).blackSelectionK1 = NULL;
	(*root).turn = 1;
	
	
	while ((*root).greenCubes + (*root).blackCubes != 0)  {
		(*root).turn = 1;
		computerPlayer(&(*root));
		if ((*root).greenCubes + (*root).blackCubes == 0) break;
		(*root).turn = -1;
		humanPlayer(&(*root));
	}
	if ((*root).turn == -1) printf("The winner is you!!");
	else printf("The winner is AI-Bot!! TRY MORE");
	return;

}







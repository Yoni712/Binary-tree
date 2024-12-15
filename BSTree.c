#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "BSTree.h"
#define _CRT_SECURE_NO_WARNINGS


/*Det Šr helt tillŒtet att lŠgga till egna hjŠlpfunktioner men de befintliga funktionerna fŒr inte Šndras*/

/* Statiska hjalpfunktioner anvands av andra funktioner i tradet och ska inte ligga i interfacet (anvandaren behover inte kanna till dessa) */


/* Skapar en tradnod med det givna datat genom att allokera minne for noden. Glom inte att initiera pekarna*/
static struct treeNode* createNode(int data)
{
	struct treeNode* treeSpace;
	treeSpace = (struct treeNode*)malloc(sizeof(struct treeNode));

	if (treeSpace != NULL) {
		treeSpace->data = data;
		treeSpace->left = NULL;
		treeSpace->right = NULL;
		return treeSpace;
	}
	
	//Glom inte att testa sa att allokeringen lyckades
 //Ersatt med ratt returvarde
}

void toArray(struct treeNode* tree, int arr[], int *counter)
{
	if (tree != NULL) {
		
		toArray(tree->left, arr, counter);
		arr[(*counter)++] = tree->data;
		toArray(tree->right, arr, counter);
	}
	
	
	//Den ska samla ihop data från trädet till array
}
/* Returnerar en dynamiskt allokerad array som innehaller tradets data sorterat */
static int* writeSortedToArray(const BSTree tree)
{
	int numbOfNodes = numberOfNodes(tree);
    int counter = 0;
	int* arr = (int*)malloc(sizeof(int) * numbOfNodes);

	if (tree != NULL) {

		toArray(tree, arr, &counter);
		/*for (int j = 0; j < numbOfNodes; j++) {
			printf("%d\n", arr[j]);
		}*/
		return arr;
	}

}

/* Bygger upp ett sorterat, balanserat trad fran en sorterad array */
static void buildTreeSortedFromArray(BSTree* tree, const int arr[], int size)
{


	if (0 >= size) {
		return;
	}
	//*tree = build(arr, 0, size);

	int mitten = size / 2;


		if (find(*tree, arr[mitten])== 1) {
			return;
		}

			insertSorted(tree, arr[mitten]);
			buildTreeSortedFromArray(tree, arr, mitten);
			buildTreeSortedFromArray(tree, arr+mitten+1, size- mitten - 1);
		
			
	/* Bygg rekursivt fran mitten.
	   Mittenelementet i en delarray skapar rot i deltradet
	   Vanster delarray bygger vanster deltrad
	   Hoger delarray bygger hoger deltrad*/
}

//static BSTree build(int* arr[], int start, int end) {
//	
//	if (start > end) {
//		return NULL;
//	}
//		
//	int mitten = (start + end) / 2;
//
//	struct treeNode* tree = createNode(arr[mitten]);
//
//	
//	tree->left = build(arr, start, mitten - 1);
//
//	tree->right = build(arr, mitten + 1, end);
//
//	return tree;
//
//}
/* Implementation av tradet, funktionerna i interfacet */

/* Skapar ett tomt trad - denna funktion ar fardig */
BSTree emptyTree(void)
{
	return NULL;
}

/* Returnerar 1 ifall tradet ar tomt, 0 annars */
int isEmpty(const BSTree tree)
{
	if (tree == NULL) {
		return 1;
	}
	return 0; // Ersatt med ratt returvarde
}

/* Satter in 'data' sorterat i *tree
 Post-condition: data finns i tradet*/
void insertSorted(BSTree * tree, int data)
{


	if (*tree == NULL) {
		*tree = createNode(data);
		assert(find(*tree, data) == 1);
		return;
	}


	if ((*tree)->data <= data) {
		insertSorted(&(*tree)->right, data);
	}
	if ((*tree)->data > data)
	{
		insertSorted(&(*tree)->left, data);
	}

	

	//return tree;
	/*Tank pa att tradet kan vara tomt vid insattning
	  Du bestammer sjalv hur dubletter ska hanteras, ska de inte accepteras eller
	  ska de laggas till vanster/hoger?.
	  Post-condition kan verifieras med hjalp av find(...)*/
}

/* Utskriftsfunktioner
   Vid anrop: anvand stdio som andra argument for att skriva ut pŒ skarmen
   Det racker att ni implementerar LR ordningarna*/
void printPreorder(const BSTree tree, FILE * textfile)
{
	struct treeNode* tempTree = tree;

	if (tempTree != NULL) {
		fprintf(textfile, "%d ", tree->data);
		printPreorder(tempTree->left, textfile);
		printPreorder(tempTree->right, textfile);
	}


}

void printInorder(const BSTree tree, FILE * textfile)
{
	struct treeNode* tempTree = tree;

	if (tempTree != NULL) {
		printInorder(tempTree->left, textfile);
		fprintf(textfile, "%d ", tree->data);
		printInorder(tempTree->right, textfile);
		
	}


}

void printPostorder(const BSTree tree, FILE * textfile)
{
	struct treeNode* tempTree = tree;
	if (tempTree != NULL) {
		printPostorder(tempTree->left, textfile);
		printPostorder(tempTree->right, textfile);
		fprintf(textfile, "%d ", tree->data);
	}
}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{

	if (tree == NULL) {
		return 0;
	}

	if (tree->data == data) {
		return 1;
	}

	if (tree->data < data) {
		
		return find(tree->right, data);
	}

	if (tree->data > data) {
		
		return find(tree->left, data);
	}


	// Tank pa att tradet kan vara tomt
	 //Ersatt med korrekt returvarde
}

/* Tar bort 'data' fran tradet om det finns */
void removeElement(BSTree * tree, int data)
{
	struct treeNode* removeTempTree = *tree;

	if (removeTempTree == NULL) {
		return;
	}
	if (find(*tree, data) == 0) {
		return;
	}

	if ((*tree)->data < data)
		removeElement(&(*tree)->right, data);

	else if ((*tree)->data > data)
		removeElement(&(*tree)->left, data);

	else {

		if ((*tree)->left == NULL && (*tree)->right == NULL) {
			free(*tree);
			*tree = NULL;
			return;
		}

		if ((*tree)->left == NULL) {
			*tree = (*tree)->right;
			free((*tree)->right);
			(*tree)->right = NULL;
			return;
		}

		if ((*tree)->right == NULL) {

			*tree = (*tree)->left;
			free((*tree)->left);
			(*tree)->left = NULL;
			return;
		}

		else {
			int RNow = minstaNode((*tree)->right);
			(*tree)->data = RNow;
			removeElement(&(*tree)->right, RNow);
		}
	}
	/* Inget data ska/kan tas bort fran ett tomt trad
	 Tre fall: Ett lov (inga barn), ett barn (vanster eller hoger), tva barn

	 Glom inte att frigora noden nar den lankats ur tradet*/
}

int minstaNode(const BSTree tree) {
	struct treeNode* TempTree = tree;

	while (TempTree->left != NULL) {
		TempTree = TempTree->left;
	}
	return TempTree->data;
}
/* Returnerar hur manga noder som totalt finns i tradet */
int numberOfNodes(const BSTree tree)
{
	if (tree == NULL) {
		return 0;
	}
	return 1 + numberOfNodes(tree->left) + numberOfNodes(tree->right);
	//Ersatt med korrekt returvarde
}

/* Returnerar hur djupt tradet ar */
int depth(const BSTree tree)
{
	if (tree == NULL) {
		return 0;
	}
	else {
		int LD = depth(tree->left);
		int RD = depth(tree->right);

		if (LD > RD) {
			return (LD+1);
		}
		else {
			return (RD+1);
		}
	}
	//Ersatt med korrekt returvarde
}

/* Returnerar minimidjupet for tradet
   Se math.h for anvandbara funktioner*/
int minDepth(const BSTree tree)
{
	if (tree == NULL) {
		return 0;
	}
	float n = numberOfNodes(tree) + 1;
	int MD = ceil((log2(n)));

	return MD;
}

static void freeArr(int* arr, int size) {
	free(arr);
	arr = NULL;
}

/* Balansera tradet sa att depth(tree) == minDepth(tree) */
void balanceTree(BSTree * tree)
{
	if (*tree == NULL) {
		return;
	}
	int numbOfNodes = numberOfNodes(*tree);
	int* arr = writeSortedToArray(*tree);
	freeTree(tree);

	buildTreeSortedFromArray(tree, arr, numbOfNodes);
	freeArr(arr, numbOfNodes);
	/* Forslag pa algoritm:
	   - overfor tradet till en dynamiskt allokerad array med writeSortedToArray()
	   - tom tradet med freeTree()
	   - bygg upp tradet rekursivt fran arrayen med buildTreeSortedFromArray()
	   - frigor minne for den dynamiskt allokerade arrayen


	   Post-conditions:
	   - tree har lika manga noder som tidigare
	   - djupet for tradet ar samma som minimumdjupet for tradet */
}

/* Tom tradet och frigor minnet for de olika noderna */
void freeTree(BSTree *tree)
{
	removeElement(tree, (*tree)->data);
	if (*tree != NULL) {
		freeTree(tree);
	}
	
	assert(isEmpty(*tree) == 1);
	// Post-condition: tradet ar tomt
}





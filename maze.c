//Data Structure and Algorithm, Korea University, Fall 2016
//Juncheol Park, School of Electrical Engineering

#include<stdio.h>
#include<malloc.h>

#define mazeSIZE 21 // Define a size of a maze
#define PATH 0 // path
#define WALL 1 // wall
#define EXIT 2 // exit
#define VISITED 3 // vitsted pathe 
#define BACKTRACKED 6 // bactracked path
#define false 0
#define true 1

typedef int Coordinate;
typedef struct Node *PtrToNode;
typedef struct stackHeader *Stack;


struct Node{
	Coordinate Xpt, Ypt;
	PtrToNode Next;
};
struct stackHeader{
	PtrToNode top;
};
typedef struct curPOS{
	Coordinate x;
	Coordinate y;
}Position;

int MAZE[mazeSIZE][mazeSIZE]= {
  // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 => Y-axis

	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //0
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, //1
	{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1}, //2
	{1, 0 ,1 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0, 1}, //3
	{1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0, 1}, //4
	{1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0, 1}, //5
	{1 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,0, 1}, //6
	{1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0, 1}, //7
	{1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,0, 1}, //8
	{1 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0, 1}, //9
	{1 ,0 ,1 ,0 ,1 ,1 ,1 ,0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, //10
	{1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, //11
	{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1}, //12
	{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1}, //13
	{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, //14
	{1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, //15
	{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, //16
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1}, //17
	{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, //18
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2}, //19
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  //20
																	 //X-axis
};

//¿Ï¼º
Stack makeStack(void);
void pushPos(Position setOfPts, Stack S);
void showMaze(const int M[][mazeSIZE]);
void showFinalMaze(int M[][mazeSIZE]);
int isEmpty(Stack S);
int possibilityToMove(Position setOfPts, int cardinalPoint);
void movePt(Position *setOfPts , int cardinalPoint);
Position popStack(Stack S);
void peekStack(Stack S);

int main(){
	Stack posStack=makeStack(); // Create a positon stack
	Position curCoordi;// The structure to save current coordinate
	showMaze(MAZE); // Show current maze first
	int cardPt =0;


	while(true){ // Check inavailablility of the start point
	printf("Start point y-axis: "); // Get a start potint;
	scanf("%d", &curCoordi.y);
	printf("Start point x-axis: ");
	scanf("%d", &curCoordi.x);
	if(MAZE[curCoordi.x][curCoordi.y] == PATH || MAZE[curCoordi.x][curCoordi.y] == EXIT)
		break;
	else
		printf("Wrong start point. Input again.\n");
	fflush(stdin); // Clear the buffer
	printf("\n");
	}

	while(true){ //Run maze
		MAZE[curCoordi.x][curCoordi.y] = VISITED;
		if( curCoordi.x == 19 && curCoordi.y==20){
			MAZE[curCoordi.x][curCoordi.y] = EXIT;
			showFinalMaze(MAZE);
			printf("Finding the path is successful!!\n");
			break;
		}
		int goStr = false;
		for(cardPt = 0 ; cardPt<4 ; cardPt++){ // North = 1, East = 2, South = 3, West = 4
			if(possibilityToMove(curCoordi, cardPt)){
				pushPos(curCoordi, posStack);
				movePt(&curCoordi, cardPt);
				goStr = true;
				break;
			}
		}
		if(!goStr){
			MAZE[curCoordi.x][curCoordi.y] = BACKTRACKED;
			if(isEmpty(posStack)){
				printf("\n No path exists.\n");
				break;
			}
			curCoordi = popStack(posStack);
		}
	}
	return 0;
}


Stack makeStack(void){
	Stack S = (Stack) malloc(sizeof(struct stackHeader));
	if(S==NULL)
		printf("Stack could not be created\n");
	S->top = NULL;
	return S;
}
void pushPos(Position setOfPts, Stack S){
	PtrToNode tmpPos;
	tmpPos = (PtrToNode) malloc(sizeof(struct Node));

	if( (setOfPts.x<0 || setOfPts.x>mazeSIZE-1 ) || (setOfPts.y<0 || setOfPts.y>mazeSIZE-1 ))
		printf("The position is out of range");

	if(tmpPos == NULL)
		printf("Out of space");

	if( MAZE[setOfPts.x][setOfPts.y] == VISITED){
		tmpPos->Next = S->top;
		tmpPos->Xpt = setOfPts.x;
		tmpPos->Ypt = setOfPts.y;
		S->top = tmpPos;
	}
}
void showMaze(const int M[][mazeSIZE]){
	int row, col;
	for(row=0 ; row<mazeSIZE; row++){
		printf(" ");
		for(col=0; col<mazeSIZE; col++)
			printf("%d ", M[row][col]);
		printf("\n");
	}
}
void showFinalMaze(int M[][mazeSIZE]){
	int i=0, j=0;
	int finalMaze[mazeSIZE][mazeSIZE]= {0};
	for(i=0; i<mazeSIZE ; i++)
		for(j=0; j<mazeSIZE ; j++){
			if( !(MAZE[i][j]==BACKTRACKED) )
				finalMaze[i][j]=MAZE[i][j];
		}

	showMaze(finalMaze);

}
int isEmpty(Stack S){
	return S->top==NULL;
}
int possibilityToMove(Position setOfPts, int cardinalPoint){
	switch(cardinalPoint){
	    case 0 : {if((MAZE[setOfPts.x-1][setOfPts.y] == PATH) || MAZE[setOfPts.x-1][setOfPts.y] ==EXIT)
					 return 1;
				 else
					 return 0;
				 break;}
		case 1 : {if((MAZE[setOfPts.x][setOfPts.y+1] == PATH) || MAZE[setOfPts.x][setOfPts.y+1] ==EXIT)
					 return 1;
				 else
					 return 0;
				 break;}
		case 2 : {if((MAZE[setOfPts.x+1][setOfPts.y] == PATH) || MAZE[setOfPts.x+1][setOfPts.y] ==EXIT)
					 return 1;
				 else
					 return 0;
				 break;}
		case 3 :if((MAZE[setOfPts.x][setOfPts.y-1] == PATH) || MAZE[setOfPts.x][setOfPts.y-1] ==EXIT)
					 return 1;
				else
					 return 0;
				 break;
	    default : return 0; break;
	}
}
void movePt(Position *setOfPts , int cardinalPoint){
	switch(cardinalPoint){
	    case 0 : setOfPts->x= setOfPts->x - 1; break;//North
		case 1 : setOfPts->y = setOfPts->y + 1; break;//East
		case 2 : setOfPts->x = setOfPts->x + 1; break;//South
		case 3 : setOfPts->y = setOfPts->y - 1; break;//West
		default : break;
	}

}
Position popStack(Stack S){
	PtrToNode tmpPast;
	Position newPos;
	if(isEmpty(S)){
		printf("** The stack is empty.\n");
	}
	else {
		tmpPast = S->top;
		S->top = tmpPast->Next;
		newPos.x = tmpPast->Xpt;
		newPos.y = tmpPast->Ypt;
		free(tmpPast);
	}
	return newPos;
}
void peekStack(Stack S){
	if(isEmpty(S))
		printf("** There is no element\n");
	else{
		printf("coordinate is (%d, %d)\n", S->top->Xpt, S->top->Ypt);}
}

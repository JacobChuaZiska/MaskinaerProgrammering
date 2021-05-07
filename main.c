#include <stdio.h>
#include <string.h>
#include<stdlib.h>
struct card {
    int rank;
    char suit;
};
struct Node  {
    struct card data;
    struct Node* next;
    struct Node* prev;
};

// struct Node* head; // global variable - pointer to head node.
//Vi vil altid læse fra head, derfor kalder vi den for head.

/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, int new_data_rank, char new_data_suit)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->data.rank = new_data_rank;
    new_node->data.suit = new_data_suit;

    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    /* 4. change prev of head node to new node */
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    /* 5. move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Function to delete the entire linked list */
void deleteList(struct Node** head_ref)
{
    /* deref head_ref to get the real head */
    struct Node* current = *head_ref;
    struct Node* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
       in the caller. */
    *head_ref = NULL;
}


//Inserts a Node at the end of the linked list
/* Given a node as prev_node, insert a new node after the given node */
//Altså indsætte midt inde mellem to noder.
void insertMiddleOf(struct Node* prev_node, int new_data_rank, char new_data_suit)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL) {
        printf("the given previous node cannot be NULL");
        return;
    }

    /* 2. allocate new node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    /* 3. put in the data  */
    new_node->data.rank = new_data_rank;
    new_node->data.suit = new_data_suit;
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. Make the next of prev_node as new_node */
    prev_node->next = new_node;

    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;

    /* 7. Change previous of new_node's next node */
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a DLL and an int, appends a new node at the end  */
void insertAtEnd(struct Node** head_ref, struct card c)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head_ref; /* used in step 5*/

    /* 2. put in the data  */
    new_node->data.rank = c.rank;
    new_node->data.suit = c.suit;

    /* 3. This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new
          node as head */
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;

    /* 7. Make last node as previous of new node */
    new_node->prev = last;

    return;
}


void Print(struct Node* node) {

    while (node != NULL) {
        printf(" %d", node->data.rank);
        printf("%c ", node->data.suit);
        printf("\n");
        node = node->next;
    }
    printf("\n");
}


/*
void splitDeckAndRiffleShuffle(struct Node*currentdeck, struct Node**split1Head, struct Node **split2Head){
    int inputSplit = 20;
    //Edge case
    if (inputSplit < 2)
    {
        *split1Head = currentdeck;
        *split2Head = NULL;
        return;
    }
    struct Node* current = currentdeck;

    int splitPosition = (inputSplit - 1) / 2;
    for (int splitIncrement = 0; splitIncrement < splitPosition; splitIncrement++) {
        current = current->next;
    }

    // Now cut at current
    *split1Head = currentdeck;
    *split2Head = current->next;
    current->next = NULL;

    struct Node* temp1 = *split1Head;
    struct Node* temp2 = *split2Head;
    while (temp1 && temp2 != NULL) {
        printf("%d",temp2->data.rank);
        printf("%c ",temp2->data.suit);
        struct card card;
        card.rank = temp1->data.rank;
        card.suit = temp1->data.suit;
        insertAtEnd(card);
        temp1 = temp1->next;
        card.rank = temp2->data.rank;
        card.suit = temp2->data.suit;
        insertAtEnd(card);
        temp2 = temp2->next;
        split1Head = temp1;
        split2Head = temp2;
        if(temp1 = NULL){
            printf("s","temp1 er Null");
        } else if (temp2 = NULL) {
            printf("s", "temp2 er Null");
        }
    }
}
 */



int writeFile(char name[], struct Node* node) {
    char text[4] = ".txt";
    strncat(name,text,4);//Tilføjer text til name
    FILE *fp;
    fp = fopen(name, "w"); //laver en fil der heller filename, og vælger w for at kunne skrive i den.
    //Med w writer vi, den overskriver altså det vi har i den fil der hedder filename.
   // fputs("Test\n", fp);
    printf("\n");
/*
    //Vi skal hen til start noden.
    while (node->prev!=NULL){
        node = node->prev;
    }
*/
    while(node != NULL) {
        printf(" %d", node->data.rank);
        printf("%c ", node->data.suit);
        //Det er ikke muligt at parse en integer til en textfil, hvis textfilen også skal indeholde strings. Så vi erstatter integeren med den tilsvarende rank.
            switch (node->data.rank) {
                case 1:
                    fputs("A",fp); break;
                case 2:
                    fputs("2",fp); break;
                case 3:
                    fputs("3",fp); break;
                case 4:
                    fputs("4",fp); break;
                case 5:
                    fputs("5",fp); break;
                case 6:
                    fputs("6",fp); break;
                case 7:
                    fputs("7",fp); break;
                case 8:
                    fputs("8",fp); break;
                case 9:
                    fputs("9",fp); break;
                case 10:
                    fputs("10",fp); break;
                case 11:
                    fputs("J",fp); break;
                case 12:
                    fputs("Q",fp); break;
                case 13:
                    fputs("K",fp); break;
            }
            switch (node->data.suit) {
                case 'C':
                    fputs("C",fp); break;
                case 'D':
                    fputs("D", fp); break;
                case 'S':
                    fputs("S", fp); break;
                case 'H':
                    fputs("H", fp); break;
            }
                fputs("\n", fp);
            //Pege på den næste node, som skal printes
                node = node->next;
        }
        printf("\n");

    fclose(fp); //lukker for filen man skriver i
    return 0;
}
/*
struct Node * readFileSwitch(char c, struct Node* node){
    struct card cardX;
    switch (c) {
        case 'A':
            cardX.rank = 1; break;
        case '2':
            cardX.rank = 2; break;
        case '3':
            cardX.rank = 3; break;
        case '4':
            cardX.rank = 4; break;
        case '5':
            cardX.rank = 5; break;
        case '6':
            cardX.rank = 6; break;
        case '7':
            cardX.rank = 7; break;
        case '8':
            cardX.rank = 8; break;
        case '9':
            cardX.rank = 9; break;
        case '1':
            cardX.rank = 10; break;
        case '0':
            //hvis 1 er en case, så kan det kun være 10. Så skal næste char, altså 0, ikke noteres.
            break;
        case 'J':
            cardX.rank = 11; break;
        case 'K':
            cardX.rank = 12; break;
        case 'D':
            if(dronningEllerDiamond==0) {
                cardX.rank = 13;
                dronningEllerDiamond++;
                break;
            } else if (dronningEllerDiamond==1){
                cardX.suit = 'D';
                dronningEllerDiamond--;
                suitOrNot=+1;
                break;
            }
        case 'S':
            cardX.suit = 'S';
            suitOrNot=+1; break;
        case 'H':
            cardX.suit = 'H';
            suitOrNot=+1; break;
        case 'C':
            cardX.suit = 'S';
            suitOrNot=+1; break;
    }
    rank = cardX.rank;

    if (suitOrNot==1){
        insertAtEnd(&node, cardX);
        suitOrNot--;
        cardX.rank = 0;
    }
    return node;
}
 */
int dronningEllerDiamond=0;
int suitOrNot=0;

struct Node * readFile(char name[]){
    char text[4] = ".txt";
    strncat(name,text,4);//Tilføjer text til name
    FILE * file_pointer;
    char c;
    struct Node* new_node = NULL;
    //Åbner filen med det navn du kom med med fopen.
    printf("----read the entire file----\n");

    file_pointer = fopen(name, "r"); //reset the pointer
    while ((c = getc(file_pointer)) != EOF) {

        printf("%c", c);

        struct card cardX;
        switch (c) {
            case 'A':
                cardX.rank = 1; break;
            case '2':
                cardX.rank = 2; break;
            case '3':
                cardX.rank = 3; break;
            case '4':
                cardX.rank = 4; break;
            case '5':
                cardX.rank = 5; break;
            case '6':
                cardX.rank = 6; break;
            case '7':
                cardX.rank = 7; break;
            case '8':
                cardX.rank = 8; break;
            case '9':
                cardX.rank = 9; break;
            case '1':
                cardX.rank = 10; break;
            case '0':
                //hvis 1 er en case, så kan det kun være 10. Så skal næste char, altså 0, ikke noteres.
                break;
            case 'J':
                cardX.rank = 11; break;
            case 'Q':
                cardX.rank = 12;break;
            case 'K':
                cardX.rank = 13; break;
            case 'S':
                cardX.suit = 'S';
                suitOrNot=1; break;
            case 'H':
                cardX.suit = 'H';
                suitOrNot=1; break;
            case 'C':
                cardX.suit = 'C';
                suitOrNot=1; break;
            case 'D' :
                cardX.suit = 'D';
                suitOrNot=1; break;
        }
        if (suitOrNot==1){
            insertAtEnd(&new_node, cardX);
            suitOrNot=0;
        }
    }
    fclose(file_pointer);
    return new_node;
}

int commando(struct Node* head) {
    char quit[] = "QQ";
    char quitGame[] = "Q";
    char name[20];
    char command[2];
    char load[] = "LD";
    char save[] = "SD";
    char startGame[] = "P";
    int i = 100;
    char delete[] = "DL";
    scanf("%s", command);
    if (strcmp(command, quit) == 0) {
        printf("You have decided to quit the game. Hope to see you again soon!\n");
        return 0;
    } else if (strcmp(command, delete)==0) {
        printf("Deleting list\n");
        //Vi skal have adressen for noden, derfor benytter vi os af &
        deleteList(&head);
        commando(head);
    }  else if (strcmp(command, save) == 0) {
        printf("Time to save a file consisting of the deck!\n");
        printf("Enter name of the file your want to write. No space, no .txt or anything. Just the name:\n");
        scanf("%s", name);
        printf("The name of the file will be: %s.txt\n", name);

        writeFile(name, head);
        commando(head);
    } else if (strcmp(command, load) == 0) {
        printf("Time to load a file to the game!\n");
        printf("Enter the name of the file you want to load. No space, no .txt or anything. Just the name of the file:\n");
        scanf("%s", name);
        printf("The name of the file you're loading will be: %s.txt\n", name);
        deleteList(&head);
        commando(readFile(name));
    } else if (strcmp(command, quitGame) == 0) {
        printf("You have chosen to quit the current game you're playing.\nYour card deck will be remembered, and you will restart the game if you enter 'P'\n");
        //Basically skal vi bare have det kortsæt som vi brugte til at starte spillet med, klar til at blive aktiveret igen med, hvis
        //brugeren vælger at trykke på P.
        commando(head);
    } else if (strcmp(command, startGame) == 0) {
        printf("You have startet the game!\n");
        //Benytter sig af den linked list kortsæt som enten allerede er i linked list(efter brugeren f.eks. allerede har spillet, og så tastet Q, men vil genstarte spille)
        //eller bare bruge det current deck, som jeg ikke ved hvad indeholder, hvis ikke brugeren har loaded er kortsæt først... Tror bare det
        //er et kortsæt der ikke er blandet.
        printf("the fuck is this: %x", i);
        commando(head);
    } else if (strcmp(command, "Pr") == 0) {
        Print(head);
        commando(head);
    } else {
        printf("You have to type one of the commands for the game\n");
        commando(head);
    }
}



int main() {
    /* Start with the empty list */
    //Initialisere en list som indeholder default kortsættet.
    //Af en eller anden grund, kunne jeg ikke lige få det til at fungere med, at lave kortsættet i en helt anden funktion.
    //Så genkender den ikke noderne du skriver det i.
    struct Node* head = NULL;
    int rankCount;
    int suitCount;
    for (suitCount= 1; suitCount <=4;suitCount++){
        for (rankCount = 1;rankCount<=13;rankCount++){

            if (suitCount == 1) {
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'C';
                insertAtEnd(&head, cardx);
            }
            if (suitCount ==2){
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'D';
                insertAtEnd(&head, cardx);
            }
            if (suitCount ==3){
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'S';
                insertAtEnd(&head, cardx);
            }
            if (suitCount ==4){
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'H';
                insertAtEnd(&head, cardx);
            }
        }
    }

    Print(head);

    //MAN SKAL KUN LAVE ÉN NODE, ELLERS GÅR DET GALT.

    printf("Welcome to the game, how may i help you?\n");
    printf("Write LD to load a deck from a file\n");
    printf("Write SD to save the deck to a file\n");
    commando(head);


}

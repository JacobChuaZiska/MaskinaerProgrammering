#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>

struct card {
    int rank;
    char suit;
};
struct Node  {
    struct card data;
    struct Node* next;
    struct Node* prev;
};


/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, struct card c)
{

    /* 1. allocate node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->data.rank = c.rank;
    new_node->data.suit = c.suit;

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


/* Given a node as prev_node, insert a new node after the given node */
//Altså indsætte midt inde mellem to noder.
void insertAfter(struct Node* prev_node, struct card c)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL) {
        printf("the given previous node cannot be NULL");
        return;
    }

    /* 2. allocate new node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    /* 3. put in the data  */
    new_node->data.rank = c.rank;
    new_node->data.suit = c.suit;
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




void deleteNode(struct Node** head_ref, int keyRank, char keySuit) {

    // Store head node
    struct Node *temp = *head_ref;

    // If head node itself holds the key to be deleted
    //Key er randomly genereret, og representere hvilket kort der skal tages.
    if (temp != NULL && temp->data.rank == keyRank && temp->data.suit == keySuit) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
       // printf("Det var den første node, og den blev derfor slettet\n");
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    //Den kører igennem hver eneste node og ser om dataen stemmer overens med det vi leder efter.
    int tal = 0;

    if (temp != NULL && temp->data.suit == keySuit){
        while (temp->data.rank != keyRank) {
            temp->prev = temp;
            temp = temp->next;
            if (temp== NULL){
                break;
            }
            tal = 1;

            if (temp!=NULL && temp->data.suit != keySuit) {
                tal=0;
                continue;
            } else if (temp!=NULL && temp->data.suit == keySuit && temp->data.rank == keyRank){
                tal=1;
                break;
            }
        }
    } else {
        while (temp->data.suit != keySuit) {
            temp->prev = temp;
            temp = temp->next;
            if (temp == NULL){
                break;
            }
       //     printf("Key: %c, og du har:%c\n", keySuit, temp->data.suit);
        }
        if (temp!=NULL && temp->data.suit == keySuit) {
            while (temp->data.rank != keyRank) {
                temp->prev = temp;
                temp = temp->next;
                if (temp== NULL){
                    break;
                }
          //      printf(" Key rank og suit: %d ____ %c\n", keyRank, keySuit);
          //      printf("    Hvad du har    %d ____ %c\n\n", temp->data.rank, temp->data.suit);
                if (temp!=NULL && temp->data.suit != keySuit) {
                    tal=0;
                    continue;
                } else if (temp!=NULL && temp->data.suit == keySuit && temp->data.rank == keyRank){
                    tal=1;
                    break;
                }
            }
        }
    }
    // Hvis while løkken ikke finder noden, så eksisterer den ikke i listen, og der printes bare en status string, og så hopper vi ud af deleteNode.
    if (temp == NULL) {
        //printf("Der er kommet en værdi ind, som ikke eksister i kortsættet\n");
        return;
    }

    //Når den rigtige node er blevet fundet, så unlink det fra linked listen.
    if (tal ==1){
    temp->prev->next = temp->next;
    free(temp); // Free memory
    //printf("Du har hævet noden ud fra listen\n");
    return;
    } else {
       // printf("Noden eksister desværre ikke i linked list, den er allerede bleve slettet\n");
        return;
    }
}

int randomOneOrTwo(){
     int oneOrTwo;
     time_t t;

     /* Intializes random number generator */
     srand((unsigned) time(&t));
     /* Random numbers from 0 to 99 */
     oneOrTwo = rand() % 100;
  //   int p = oneOrTwo %2;

    return oneOrTwo;
}


struct Node * ShuffleDeck(struct Node* node){
    //https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
    int randomNumber, antal=1;
    int tal = rand() %1000;
    struct Node* new_node = NULL;
    while (node != NULL){

        /* Intializes random number generator */
        srand(tal);
        /* Random numbers from 0 to 99 */
            randomNumber = rand() % 100;
            tal+=randomNumber;

//        randomNumber = randomOneOrTwo();

        //Går igennem alle kortene
        struct card cardZ;
        cardZ.rank = node->data.rank;
        cardZ.suit = node->data.suit;

        if (randomNumber > 66 && randomNumber <= 99 && new_node!=NULL) {
//            printf("Du tilføjede kort nr. %d som var: %d%c på 2. plads\n", antal, cardZ.rank, cardZ.suit);
            antal+=1;
            insertAfter(new_node, cardZ);
            //Videre til næste kort du har i bunken
            node = node->next;
        } else if (randomNumber > 33 && randomNumber <= 66) {
//            printf("Du tilføjede kort nr. %d: %d%c foran\n", antal, cardZ.rank, cardZ.suit);
            antal+=1;
            push(&new_node,cardZ);
            node = node->next;
        } else if (randomNumber <= 33) {
//            printf("Du tilføjede kort nr. %d: %d%c bagved\n", antal, cardZ.rank, cardZ.suit);
            antal+=1;
            //Indsætter på adressen & for new_node.
            insertAtEnd(&new_node, cardZ);
            node = node->next;
        } else{
//            printf("Trying again\n");
        }
        Print(new_node);


     }
    return new_node;
}

void splitDeckAndRiffleShuffle(struct Node* node){
    struct Node* split1Head = NULL;
    struct Node* split2Head = NULL;
    int inputSplit = 20;

    struct Node* current = node;

    int splitPosition = (inputSplit - 1) / 2;
    for (int splitIncrement = 0; splitIncrement < splitPosition; splitIncrement++) {
        current = current->next;
    }

    // Seperate deck after current.
    split1Head = node;
    split2Head = current->next;
    current->next = NULL;

    //tempoary heads, and the head of new deck gets defined.
    struct Node* temp1 = split1Head;
    struct Node* temp2 = split2Head;
    struct Node* newHead = NULL;
    while (1) {
        printf("%s","Start af while loop");
        struct card cardz;
        cardz.rank = temp1->data.rank;
        cardz.suit = temp1->data.suit;
        push(&newHead,cardz);
        temp1 = temp1->next;
        struct card cardx;
        cardx.rank = temp2->data.rank;
        cardx.suit = temp2->data.suit;
        push(&newHead,cardx);
        temp2 = temp2->next;

        printf("%s","Slutning af while loop");
        if(temp1 == NULL){
            printf("%s","temp1 er Null");
            while(temp2!= NULL){
                struct card cardx;
                cardx.rank = temp2->data.rank;
                cardx.suit = temp2->data.suit;
                insertAtEnd(&newHead,cardx);
                temp2 = temp2->next;
            }
            break;
        } else if (temp2 == NULL) {
            printf("%s", "temp2 er Null");
            while(temp1!= NULL){
                struct card cardz;
                cardz.rank = temp2->data.rank;
                cardz.suit = temp2->data.suit;
                insertAtEnd(&newHead,cardz);
                temp1 = temp1->next;
            }
            break;
        }
    }
    Print(newHead);
}







int writeFile(char name[], struct Node* node) {
    char text[4] = ".txt";
    strncat(name,text,4);//Tilføjer text til name
    FILE *fp;
    fp = fopen(name, "w"); //laver en fil der heller filename, og vælger w for at kunne skrive i den.
    //Med w writer vi, den overskriver altså det vi har i den fil der hedder filename.
   // fputs("Test\n", fp);
    printf("\n");

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


struct Node * readFile(char name[]){
    int suitOrNot=0;
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
    char shuffleDeck[] = "SR";
    scanf("%s", command);
    if (strcmp(command, quit) == 0) {
        printf("You have decided to quit the game. Hope to see you again soon!\n");
        return 0;
    } else if (strcmp(command, shuffleDeck)==0){
        printf("Shuffling deck\n");
        commando(ShuffleDeck(head));
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
        printf("Not implemented %x", i);
        commando(head);
    } else if (strcmp(command, "Pr") == 0) {
        Print(head);
        commando(head);
    }
    else if (strcmp(command,"SI") == 0){
        splitDeckAndRiffleShuffle(head);
        commando(head);
    }
    else {
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
    printf("Other commands include: QQ, DL, SR, Pr, SI \n");
    commando(head);


}

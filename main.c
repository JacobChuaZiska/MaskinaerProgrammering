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

struct Node* head; // global variable - pointer to head node.

//Creates a new Node and returns pointer to it.
struct Node* GetNewNode(struct card newCard) {
    struct Node* newNode
            = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newCard;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

//Inserts a Node at the beginning of the linked list
void insertAtStart(struct card x) {
    struct Node* newNode = GetNewNode(x);
    if(head == NULL) {
        head = newNode;
        return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
}




//Inserts a Node at the end of the linked list
void insertAtEnd(struct card x) {
    struct Node* temp = head;
    struct Node* newNode = GetNewNode(x);
    if(head == NULL) {
        head = newNode;
        return;
    }
    while(temp->next != NULL) temp = temp->next; // Go To last Node
    temp->next = newNode;
    newNode->prev = temp;
}

void Print() {
    struct Node* temp = head;
    while(temp != NULL) {
        printf("%d",temp->data.rank);
        printf("%c ",temp->data.suit);
        temp = temp->next;
    }
    printf("\n");
}



void defaultDeck(){
    int rankCount;
    int suitCount;
    for (suitCount= 1; suitCount <=4;suitCount++){
        for (rankCount = 1;rankCount<=13;rankCount++){

            if (suitCount == 1) {
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'C';
                insertAtEnd(cardx);
            }
            if (suitCount ==2){
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'D';
                insertAtEnd(cardx);
            }
            if (suitCount ==3){
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'S';
                insertAtEnd(cardx);
            }
            if (suitCount ==4){
                struct card cardx;
                cardx.rank = rankCount;
                cardx.suit = 'H';
                insertAtEnd(cardx);
            }
        }
    }
}

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



int writeFile(char name[]) {
    char text[4] = ".txt";
    strncat(name,text,4);//Tilføjer text til name
    FILE *fp;
    fp = fopen(name, "w"); //laver en fil der heller filename, og vælger w for at kunne skrive i den.
    //Med w writer vi, den overskriver altså det vi har i den fil der hedder filename.
    fputs("Test\n", fp);


        struct Node* temp = head;

        while(temp != NULL) {
        //Det er ikke muligt at parse en integer til en textfil, hvis textfilen også skal indeholde strings. Så vi erstatter integeren med den tilsvarende rank.
            switch (temp->data.rank) {
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
                    fputs("D",fp); break;
                case 13:
                    fputs("K",fp); break;
            }
            switch (temp->data.suit) {
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
                temp = temp->next;
        }
        printf("\n");

        /*
    char kort[52];
    for (int i = 0; i < 52; ++i) {
        struct Node* temp = head;
        while(temp != NULL) {
            kort[0] = ("%d",temp->data.rank);
            printf("%c ",temp->data.suit);
            temp = temp->next;
        }
        printf("\n");

    }
         */



    fclose(fp); //lukker for filen man skriver i
    return 0;
}
int dronningEllerDiamond=0;

int readFileSwitch(char c){
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
        case 'D': {;
            if(dronningEllerDiamond==0) {
                cardX.rank = 13;
                dronningEllerDiamond++;
                break;
            } else if (dronningEllerDiamond==1){
                cardX.suit = 'D';
                dronningEllerDiamond--;
                break;
            }
            case 'S':
                cardX.suit = 'S';
        }
            break;
        case 'H':
            cardX.rank = 'H'; break;
        case 'C':
            cardX.rank = 'S'; break;
    }
    struct Node* newNode = GetNewNode(cardX);



}

int readFile(char name[]){
    char text[4] = ".txt";
    strncat(name,text,4);//Tilføjer text til name
    FILE * file_pointer;
    char c;
    //Åbner filen med det navn du kom med med fopen.
    printf("----read the entire file----\n");

    file_pointer = fopen(name, "r"); //reset the pointer
    while ((c = getc(file_pointer)) != EOF) {
        readFileSwitch(c);
        printf("%c", c);
    }
    fclose(file_pointer);
    return 0;
}

int commando() {
    char quit[] = "QQ";
    char quitGame[] = "Q";
    char name[20];
    char command[2];
    char load[] = "LD";
    char save[] = "SD";
    char startGame[] = "P";
    int i = 100;
    scanf("%s", command);
    if (strcmp(command, quit) == 0) {
        printf("You have decided to quit the game. Hope to see you again soon!\n");
        return 0;
    } else if (strcmp(command, save) == 0) {
        printf("Time to save a file consisting of the deck!\n");
        printf("Enter name of the file your want to write. No space, no .txt or anything. Just the name:\n");
        scanf("%s", name);
        printf("The name of the file will be: %s.txt\n", name);
        printf("Bare en test: %c", *name);
        writeFile(name);
        commando();
    } else if (strcmp(command, load) == 0) {
        printf("Time to load a file to the game!\n");
        printf("Enter the name of the file you want to load. No space, no .txt or anything. Just the name of the file:\n");
        scanf("%s", name);
        printf("The name of the file you're loading will be: %s.txt\n", name);
        readFile(name);
        commando();
    } else if (strcmp(command, quitGame) == 0) {
        printf("You have chosen to quit the current game you're playing.\nYour card deck will be remembered, and you will restart the game if you enter 'P'\n");
        //Basically skal vi bare have det kortsæt som vi brugte til at starte spillet med, klar til at blive aktiveret igen med, hvis
        //brugeren vælger at trykke på P.
        commando();
    } else if (strcmp(command, startGame) == 0) {
        printf("You have startet the game!\n");
        //Benytter sig af den linked list kortsæt som enten allerede er i linked list(efter brugeren f.eks. allerede har spillet, og så tastet Q, men vil genstarte spille)
        //eller bare bruge det current deck, som jeg ikke ved hvad indeholder, hvis ikke brugeren har loaded er kortsæt først... Tror bare det
        //er et kortsæt der ikke er blandet.
        printf("the fuck is this: %x", i);
        commando();
    } else if (strcmp(command, "Pr") == 0) {
        Print();
        commando();
    } else {
        printf("You have to type one of the commands for the game\n");
        commando();
    }
}


int main() {
    defaultDeck();
    Print();

    // Calling an Insert and printing list both in forward as well as reverse direction.
   /*
    struct card card1;
    card1.rank = '1';
    card1.suit = 'A';
    struct card card2;
    card2.rank = '2';
    card2.suit = 'A';

    insertAtEnd(card1);
    insertAtEnd(card2);
    */
    printf("Welcome to the game, how may i help you?\n");
    printf("Write LD to load a deck from a file\n");
    printf("Write SD to save the deck to a file\n");
    commando();


}

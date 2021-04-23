#include <stdio.h>
#include <string.h>
int writeFile(char name[]) {
    char text[4] = ".txt";
    int i;
    char theLinkedList[104];
    strncat(name,text,4);//Tilføjer text til name
    FILE *fp;
    fp = fopen(name, "w"); //laver en fil der heller filename, og vælger w for at kunne skrive i den.
    //Med w writer vi, den overskriver altså det vi har i den fil der hedder filename.
    fputs("Bare en lille test\n", fp);
    fputs("Virker det?\n", fp);
    fputs("Fuck ja det virker\n", fp);

    //Jeg tror dog vi skal bruge den her, ellers skal vi skrive 52 linjer kode:

    //for (i = 0; theLinkedList[i] != EOF; i++) {
        /* write to file using fputc() function */
     //   fputc(theLinkedList[i], fp);
    //}


    fclose(fp); //lukker for filen man skriver i
    return 0;
}

int readFile(char name[]){
    char text[4] = ".txt";
    strncat(name,text,4);//Tilføjer text til name
    FILE * file_pointer;
    char buffer[30], c;

    file_pointer = fopen(name, "r");
    printf("----read a line----\n");
    fgets(buffer, 50, file_pointer);
    printf("%s\n", buffer);

    printf("----read and parse data----\n");
    file_pointer = fopen(name, "r"); //reset the pointer
    char str1[10], str2[10], str3[20], str4[10];
    fscanf(file_pointer, "%s %s %s %s", str1, str2, str3, str4);
    printf("Read String1 |%s|\n", str1);
    printf("Read String2 |%s|\n", str2);
    printf("Read String3 |%s|\n", str3);
    printf("Read String4 |%s|\n", str4);

    printf("----read the entire file----\n");

    file_pointer = fopen(name, "r"); //reset the pointer
    while ((c = getc(file_pointer)) != EOF) printf("%c", c);
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
    } else {
        printf("You have to type one of the commands for the game\n");
        commando();
    }
}


int main() {

    printf("Welcome to the game, how may i help you?\n");
    printf("Write LD to load a deck from a file\n");
    printf("Write SD to save the deck to a file\n");
    commando();


}

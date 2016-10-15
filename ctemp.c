#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

bool careIfExists = true;

void PrintTemplate(FILE* fp) {
   fprintf(fp, "#include <stdio.h>\n");
   fprintf(fp, "\nint main(int argc, char *argv[]) {\n");
   fprintf(fp, "\n\n   return 0;\n}");
   return;
}

void ProcessArguments(char* fileName, int argc, char **argv) {  
   strcpy(fileName, argv[1]);
    
   if (strchr(fileName, '.') && strcmp(strchr(fileName, '.'), ".c") != 0) {
      *(strchr(fileName, '.')) = '\0';
      careIfExists = false;
      strcat(fileName, ".c"); 
   }
   else if (!strchr(fileName, '.')) {
      strcat(fileName, ".c");
   }

   return; 
}

int main(int argc, char **argv) {
   FILE* fp = NULL;

   if (argc != 2) {
      printf("Usage: ctemp \"filename\"\n");
      return -1;
   }

   char fileName[strlen(argv[1])];
 
   ProcessArguments(fileName, argc, argv);
  
   if (careIfExists && access(fileName, 0) == 0) {
      printf("File already exists\n");
      return -1;
   }
 
   char* vimCommand = malloc(strlen(fileName) + 5);
   strcat(strcat(vimCommand, "vim "), fileName);

   fp = fopen(fileName, "w");
   
   if (fp == NULL) {
      printf("Error: Could not open file.\n");
      return -1;
   }

   PrintTemplate(fp);   
  
   fclose(fp);

   system(vimCommand);
 
   return 0;
}

#include <stdio.h>
#include <windows.h>


#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle;
static DWORD outModeInit;

void setupConsole(void) {
DWORD outMode = 0;
stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

if(stdoutHandle == INVALID_HANDLE_VALUE) {
exit(GetLastError());
}

if(!GetConsoleMode(stdoutHandle, &outMode)) {
exit(GetLastError());
}

outModeInit = outMode;

    // Enable ANSI escape codes
 outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

 if(!SetConsoleMode(stdoutHandle, outMode)) {
     exit(GetLastError());
   }  
 }

void restoreConsole(void) {
  // Reset colors
  printf("\x1b[0m\x1b[0m");  
  
    // Reset console mode
if(!SetConsoleMode(stdoutHandle, outModeInit)) {
     exit(GetLastError());
   }
}


void printOpening();

int beginningAddress=0x10188;
int whichCharacter;

int main(void) {
   setupConsole();
   printOpening();
   scanf("%d", &whichCharacter);  

   FILE *f;
   unsigned char c[1];

   f = fopen("pzfe.03", "r");

   int OffsetMove=0,OffsetMoveRow=0;

   printf(" 1 | 2 | 3 | 4 | 5 | 6 |\n");

   for(int row=0;row<12;row++)
   {
      for(int col=0;col<6;col++)
      {
         fseek(f, (beginningAddress+(whichCharacter*192)+OffsetMove+OffsetMoveRow), SEEK_SET);
         fread(c, sizeof(unsigned char), 1, f);

         //printf("c[0] is %d",c[0]);

         switch(c[0])
        {
         case 00:
         printf("ERROR printing 00s");break;

         case 1://blue
         printf("\x1b[0m\x1b[44m");break;

         case 2://yellow
         printf("\x1b[0m\x1b[43m");break;
         
         case 3://green
         printf("\x1b[0m\x1b[42m");break;

         case 4://red
         printf("\x1b[0m\x1b[41m");break;

         case 0x11://blue crash gem
         printf("\x1b[30m\x1b[44m");break;         

         case 0x12://yellow crash gem
         printf("\x1b[30m\x1b[43m");break;    

         case 0x13://green crash gem
         printf("\x1b[30m\x1b[42m");break;  
         
        }

        if(c[0]>0 && c[0]<=4){printf("|**|");}
        else if(c[0]>=0x11 && c[0]<=0x13){printf("|CC|");}

        printf("\x1b[0m\x1b[0m"); 
        //if(OffsetMove<10)printf("-");
        OffsetMove+=2;
      }

      printf(" %d\n",row+1);
      OffsetMove=0;
      OffsetMoveRow+=16;

   }

   scanf("%d", &whichCharacter); //because trashboat was crashing on exit, maybe the fclose
   fclose(f);
   restoreConsole();
   return 0;
}


void printOpening()
{
   printf("SPF2T character drop pattern reader\n");
   printf("-----------------------------------\n");
   printf("0: Morrigan\n");
   printf("1: Chun-Li\n");
   printf("2: Ryu\n");
   printf("3: Ken\n");
   printf("4: Hsien-Ko\n");
   printf("5: Donovan\n");
   printf("6: Felicia\n");
   printf("7: Sakura\n");
   printf("8: Devilot\n");
   printf("9: Akuma\n");
   printf("10 (not A): Dan\n");
   printf("input your selection:\n");
}
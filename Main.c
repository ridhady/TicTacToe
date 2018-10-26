#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "boolean.h"
#include <string.h>

char TacTic[10] ={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char state[200][10][10];
char curState[10];
int nState;
int input;
char statelewat[10][10];
int nlewat = 1;


void welcomeScreen();
/* I.S : sembarang
  F.S : Welcome Screen tergambar di layar */
void papanPermainan();
/* I.S : Sembarang;
  F.s : Papan Tic Tac Toe muncul di layar dengan isi yang sesuai, menggunakan clear screen setiap kali papanPermainan dipanggil*/

boolean cekMenang(char mark);
/* Mengembalikan true apabila input Mark (O atau X) memenuhi kondisi cekMenang
yaitu {1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9} atau {3,5,7} */
int cekHasil();
/* Mengembalikan -1 jika pengguna kalah, 1 jika pengguna menang, dan 0 jika seri.*/
boolean cekMove();
/* Mengembalikan true, jika gerakan yang dipilih oleh pengguna valid, yaitu ketika petak yang dipilih masih kosong, dan 1<= input <= 9 */

void playerTurn();
/* I.S : sembarang
  F.S : Player memasukan nilai yang valid dan nilai tersimpan pada array TacTic */
void cpuTurn();
/* I.S : Sembarang
  F.S : Komputer memilih state selanjutnya dengan merespon masukan dari Pengguna*/
void importExternal();
/* I.s : File Eksternal tersedia dan terdefinisi
  F.S : Isi dari File Eksternal selesai dimasukan ke dalam Matriks State dalam Program*/
void nextState();
/* I.S : curState terdefinisi
  F.S : curState berubah sesuai dengan respon komputer terhadap masukan user dan terdefinisi*/

int main(){
  int player;
  int turn = 1;
  char XO;

  welcomeScreen();
  printf("Masukan nilai = ");
  scanf("%d", &player);
  printf("\n");
  while ((player != 1) && (player != 2)){
    printf("Nilai salah!\n");
    printf("Masukan ulang = ");
    scanf("%d", &player);
  }
  if (player == 1){
    TacTic[5] = 'X';
    input = 5;
  } else {
    TacTic[5] = 'O';
  }
  strncpy(curState, TacTic+1, 9);
  strncpy(statelewat[nlewat], curState, 10);
  nlewat++;
  player--;
  importExternal();
  while (cekHasil() == 0 && turn < 9){
    papanPermainan();
    if (((player + turn) % 2) == 0){
      playerTurn();
    } else {
      cpuTurn();
    }
    turn++;
  }
  papanPermainan();
  switch(cekHasil()){
    case 0:
      printf("Hasilnya Seri. Semangat!\n");
      break;
    case -1:
      printf("Kamu Kalah\n");
      break;
    case 1:
      printf("Selamat, kamu menang\n");
      break;
  }
  printf("State yang dilewati\n");
  int j;
  for (j = 1; j< nlewat; j++)
    printf("%s\n", statelewat[j]);

  return 0;
}

void welcomeScreen(){
  system("cls");

  printf("\t SELAMAT DATANG PEMAIN!\n\n\n");
  printf("\t |                   |\n");
  printf("\t |                   |\n");
  printf("\t | Anda akan bermain |\n");
  printf("\t |      sebagai      |\n");
  printf("\t |      | 'X' |      |\n");
  printf("\t |   Silahkan pilih  |\n");
  printf("\t |    giliran Anda   |\n");
  printf("\t |                   |\n");
  printf("\t |   Masukan (1/2)?  |\n");
}

void papanPermainan(){
  system("cls");

  printf("\n\n\tTic Tac Toe Ajib Ajib\n\n");
  printf("\t___________________\n");
  printf("\t|     |     |     |\n");
  printf("\t|  %c  |  %c  |  %c  |\n", TacTic[1], TacTic[2], TacTic[3]);
  printf("\t|_____|_____|_____|\n");
  printf("\t|     |     |     |\n");
  printf("\t|  %c  |  %c  |  %c  |\n", TacTic[4], TacTic[5], TacTic[6]);
  printf("\t|_____|_____|_____|\n");
  printf("\t|     |     |     |\n");
  printf("\t|  %c  |  %c  |  %c  |\n", TacTic[7], TacTic[8], TacTic[9]);
  printf("\t|_____|_____|_____|\n\n");
}

boolean cekMenang(char mark){
  if ((TacTic[1] == TacTic[2]) && (TacTic[2] == TacTic[3]) && (TacTic[1] == mark)){
    return true;
  } else if ((TacTic[4] == TacTic[5]) && (TacTic[5] == TacTic[6]) && (TacTic[4] == mark)){
    return true;
  } else if ((TacTic[7] == TacTic[8]) && (TacTic[8] == TacTic[9]) && (TacTic[7] == mark)){
    return true;
  } else if ((TacTic[1] == TacTic[4]) && (TacTic[4] == TacTic[7]) && (TacTic[1] == mark)){
    return true;
  } else if ((TacTic[2] == TacTic[5]) && (TacTic[5] == TacTic[8]) && (TacTic[2] == mark)){
    return true;
  } else if ((TacTic[3] == TacTic[6]) && (TacTic[6] == TacTic[9]) && (TacTic[3] == mark)){
    return true;
  } else if ((TacTic[1] == TacTic[5]) && (TacTic[5] == TacTic[9]) && (TacTic[5] == mark)){
    return true;
  } else if ((TacTic[3] == TacTic[5]) && (TacTic[5] == TacTic[7]) && (TacTic[5] == mark)){
    return true;
  } else {
    return false;
  }
}

int cekHasil(){
  if (cekMenang('O')) {
    return -1;
  } else if (cekMenang('X')){
    return 1;
  } else {
    return 0;
  }
}

boolean cekMove(){
  if ((input == 1) && (TacTic[1] == '1')){
    return true;
  } else if ((input == 2) && (TacTic[2] == '2')){
    return true;
  } else if ((input == 3) && (TacTic[3] == '3')){
    return true;
  } else if ((input == 4) && (TacTic[4] == '4')){
    return true;
  } else if ((input == 5) && (TacTic[5] == '5')){
    return true;
  } else if ((input == 6) && (TacTic[6] == '6')){
    return true;
  } else if ((input == 7) && (TacTic[7] == '7')){
    return true;
  } else if ((input == 8) && (TacTic[8] == '8')){
    return true;
  } else if ((input == 9) && (TacTic[9] == '9')){
    return true;
  } else {
    return false;
  }
}



void playerTurn(){
  printf("\nMasukan gerakan anda selanjutnya : ");
  scanf("%d", &input );
  while ( (input > 9 || input < 1) || (cekMove() == false)){
    printf("Masukan tidak sahih\n");
    printf("Masukan gerakan anda selanjutnya : ");
    scanf("%d", &input );
  }
  TacTic[input] = 'X';
}

void cpuTurn(){
  nextState();
  strncpy(TacTic+1, curState, 9);
  strncpy(statelewat[nlewat], curState, 10);
  nlewat++;
}

void importExternal(){
   FILE *fp;
   int retval;
   char CC;
   fp = fopen("TTTStates.txt" , "r");
   int i;

   if(fp == NULL) {
      perror("Error opening file");
   } else {
	   i = 1;
     retval = fscanf(fp, "%c", &CC);
		 while (retval != EOF){
			fscanf(fp, "%s %s %s %s %s %s %s %s %s %s", state[i][0], state[i][1], state[i][2], state[i][3], state[i][4], state[i][5], state[i][6], state[i][7], state[i][8], state[i][9]);
			retval = fscanf(fp, "%c", &CC);
      i++;
		 }
     nState = i - 1;
	 }

   fclose(fp);
}

void nextState(){
  boolean found = false;
  boolean sama;
  int i = 1;
  int j;

  while ((i <= nState) && (!found)){
    sama = true;
    j = 0;
    while ((j<10) && sama){
      if(curState[j] != state[i][0][j]){
        sama = false;
      } else {
        j++;
      }
    }
    if (sama) {
      found = true;
    } else {
      i++;
    }
  }
  //Ganti curState dengan state yang sudah disiapkan
  strncpy(curState, state[i][input], 10);

}

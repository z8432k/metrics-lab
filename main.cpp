#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <iomanip>

//using namespace std;

const int MMAX=500,
          size_FIO=40,
          size_GROUP=6,
          size_GRADE=5;

// ��������� - ������ � ����� ��������
struct Student {
  char fio[size_FIO+2];      // ���
  char group[size_GROUP+2];  // ������
  char grade[size_GRADE+1];  // ������
  float avgGrade;            // ������� ������
  int NumFIO;              // ����� �� ���
  int NumGroup;            // ����� �� ������
  int NumAvgGrade;         // ����� �� �������� �����
};

// ������
Student StudArray[MMAX+1];           // ������ ������ � ���������
int StudNum=0;                 // ���������� ���������
// ����������� ��: 1-���, 2-������, 3-������� ������
char sort;

// ���� �������

enum ConsoleColor
{
    Black         = 0,
    Blue          = 1,
    Green         = 2,
    Cyan          = 3,
    Red           = 4,
    Magenta       = 5,
    Brown         = 6,
    LightGray     = 7,
    DarkGray      = 8,
    LightBlue     = 9,
    LightGreen    = 10,
    LightCyan     = 11,
    LightRed      = 12,
    LightMagenta  = 13,
    Yellow        = 14,
    White         = 15
};

// ��������� ����� ������ � ����
void SetColor(int text, int background)
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

// ���������� ������ � ������� �� ������
void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

// ��������� ������ � ������
// a- ������, b- �����
int compare(char * a,char * b) {
  int k;
  int n;
  k=1;
  for (n=0;n<strlen(b);n++)
    if (a[n]!=b[n]) k=0;
  return k;
}

// ����� ������ �� �����
void output(int menuPOS,int cursPOS, float SetAvgGrade) {
  int n;
  int m;
  int nd;
  m=menuPOS;
// ������� ������
  SetColor(15,1);
  system("cls");
  std::cout << "������� ���� ( ";
  std::cout << " ������ �� ��. ����� = " << SetAvgGrade << " ): " << std::endl;
// ����� �������� ���������
  for (n=1;n<20;n++) {
  // ���� ������� ������, ��������� ������
    if (n==cursPOS) {
      SetColor(15,14);
    } else {
      SetColor(15,1);
    }
    if (m<(StudNum+1)) {
      nd=0;
      // ����� �������� � ������ ��������
      switch (sort) {
        case(1):
          while (StudArray[nd].NumFIO!=m) nd++;
          break;
        case(2):
          while (StudArray[nd].NumGroup!=m) nd++;
          break;
        case(3):
          while (StudArray[nd].NumAvgGrade!=m) nd++;
          break;
      }
      // ����� ������ � �������� �� �����
      gotoxy(1,(m-menuPOS+1));
        if (StudArray[nd].avgGrade > SetAvgGrade) {
          printf("%3d %40s %6s %5s %1.2f\n",m,StudArray[nd].fio,StudArray[nd].group,StudArray[nd].grade,StudArray[nd].avgGrade);
        }
        m++;
    }
  }
  SetColor(15,1);
}

// ��������� ����
int menu(int x,int y,char * capt) {
  int n,m;	// ��������
  int num;	// ���������� �������
  int k;	// ��������� �����
  char * pt;	// ��������� ��������� �� ������
  char c;	// ��������� � ���������� ������
// ��������� ���������� �������
  num=strlen(capt)/20;
// ������ �� ������� �������
  k=0;
// ����������� ���� ���������
  for (;;) {
// ����� ����
    pt=capt;
    for (n=0;n<num;n++) {
      gotoxy(x,y+n);
  // �������� ������, �� ������� ��������� ������
      if (n==k) {
      // ��������
	SetColor(14,12);
      } else {
      // ����������
	SetColor(1,3);
      }
      printf("%d) ",n+1);
      for (m=0;m<20;m++) printf("%c",*(pt++));
    }
    SetColor(1,3);
  // ����� ����������
    c=getch();
    if (!c) c=getch();
  // ��������, �� ������ �� ������� � ������
    if (((c-'1')>=0)&&((c-'1')<num)) {
  // ��������� ��������� � ����������� �� ������� �����
      k=c-'1';
  // ������ � ����� ���������� ������� ENTER
      ungetch(13);
    } else {
    // ������
      switch(c) {
        // �����
        case (72):
	  if (k>0) k--; else k=num-1;
	  break;
        // ����
        case (80):
	  if (k<(num-1)) k++; else k=0;
	  break;
        // ����� �� ESC - ������������ -1
        case (27):
	  return -1;
        // ����� �� ENTER - ������������ ����� ������
        case (13): return k;
      }
    }
  }
}

// ���� ������
// s - ��������� �� ������
// lng - ������������ ������
// x,y - ����������
void SInput(char *s,int lng,int x,int y) {
  char rs[100];         // ��������� ������
  strcpy(rs,s);         // ����������� ������� ������
  int n;                // �������
  char c;               // ������
// ����� ������ ������
  SetColor(15,2);
  gotoxy(x,y);
  for (n=0;n<lng;n++) printf(" ");
  lng--;
  n=strlen(s);          // ��������� �������
  do {
  // ����� ������
    gotoxy(x,y);
    printf("%s  ",s);
    gotoxy(x+n,y);
    c=getch();          // ���������� ������� � ����������
    if ((c!=13)&&(c!=27)&&(c!=8)) {
    // ������ ���������� �������
      if (n<(lng-1)) {
      // ���������� �������
        s[n+1]=0;
        s[n]=c;
        n++;
      }
    } else {
      if (c==8) {
      // ������ ������� BackSpace
        if (n>0) {
          n--;
          s[n]=0;
        }
      }
    }
// �����, ���� ESC ��� ENTER
  } while ((c!=27)&&(c!=13));
  if(c==27) strcpy(s,rs);       // �������������� ������
// �������� ������
  SetColor(7,0);
  gotoxy(x,y);
  for (n=0;n<lng+1;n++) printf(" ");
}

// ���� ������
// s - ��������� �� ������
// lng - ������������ ������
// x,y - ����������
float GInput(char *s, int lng,int x,int y) {
  char rs[100];         // ��������� ������
  strcpy(rs,s);         // ����������� ������� ������
  int n=0, k=0;         // �������
  char c;               // ������
  float avgGRADE;       // C������ ������
// ����� ������ ������
  SetColor(15,2);
  gotoxy(x,y);
  for (n=0;n<lng;n++) printf(" ");
//  lng--;
  n=strlen(s);          // ��������� �������
  do {
  // ����� ������
    gotoxy(x,y);
    printf("%s  ",s);
    gotoxy(x+n,y);
    c=getch();          // ���������� ������� � ����������
if ((c!=13)&&(c!=27)&&(c!=8)&&((c==49)||(c==50)||(c==51)||(c==52)||(c==53))) {
    // ������ ����� �� 1 �� 5
      if (n<(lng-1)) {
      // ���������� �������
        s[n+1]=0;
        s[n]=c;
        n++;
      }
    } else {
      if (c==8) {
      // ������ ������� BackSpace
        if (n>0) {
          n--;
          s[n]=0;
        }
      }
    }
// �����, ���� ESC ��� ENTER
  } while ((c!=27)&&(c!=13));
// ������� ������� ����
    avgGRADE=0;
    for (n=0;n<lng-1;n++) {
      if (s[n]>0) {
        avgGRADE+=(float)(s[n]-48);
        k++;
      }
    }
    if (k==0) {
      avgGRADE=0;
    } else {
      avgGRADE = avgGRADE / k;
    }
    return avgGRADE;
  if(c==27) strcpy(s,rs);       // �������������� ������
// �������� ������
  SetColor(7,0);
  gotoxy(x,y);
  for (n=0;n<lng+1;n++) printf(" ");
}

// �������������� ������� - ���������� ������� ���������
// �� �������� ��� ������� ���� ������
void index() {
  int n,m;                      // ��������
  char mxc[100];                // �������� ����������� ��������
  int nm;                       // ����� ���������� ��������
// �������� ������ ��������
  for (n=0;n<StudNum;n++) {
    StudArray[n].NumFIO=0;
    StudArray[n].NumGroup=0;
  }
// ���������� �� ���
  for (m=0;m<StudNum;m++) {
  // ����� ��������� ����������
    strcpy(mxc,"\x0ffh");
    for (n=0;n<StudNum;n++) if (StudArray[n].NumFIO==0)
      if (strcmp(StudArray[n].fio,mxc)<0) {
      strcpy(mxc,StudArray[n].fio);
      nm=n;
    }
  // ���������� �� ���������� ������
    StudArray[nm].NumFIO=m+1;
  }
// ���������� �� ������
  for (m=0;m<StudNum;m++) {
  // ����� ���������� �����������
    strcpy(mxc,"\x0ffh");
    for (n=0;n<StudNum;n++) if (StudArray[n].NumGroup==0)
      if (strcmp(StudArray[n].group,mxc)<0) {
      strcpy(mxc,StudArray[n].group);
      nm=n;
    }
  // ���������� ��� ���������� �������
    StudArray[nm].NumGroup=m+1;
  }

  /*���������� �� ������� ������
  for (m=0;m<StudNum;m++) {
  // ����� ���������� ������
    strcpy(mxc,"\x0ffh");
    for (n=0;n<StudNum;n++)
      if (StudArray[n].NumAvgGrade==0)
        if (strcmp(StudArray[n].grade,mxc)<0) {
          strcpy(mxc,StudArray[n].grade);
          nm=n;
        }
    StudArray[nm].NumAvgGrade=m+1;
  }*/
}



// �������������� �������� �������
void edit(int ed) {
  system("cls");
// ���������
  int n;
  int en=0;
  char c;
  for(;;) {
  // ����� ������
    for (n=0;n<3;n++) {
      if (n==en) {
        SetColor(15,12);
      } else {
        SetColor(7,1);
      }
      gotoxy(15,6+2*n);
    // ����� ������ �� ����� ���������
      switch(n) {
        case 0:
          printf(" ���:              %40s",StudArray[ed].fio);
          break;
        case 1:
          printf(" ������:           %6s",StudArray[ed].group);
          break;
        case 2:
          printf(" ������:           %5s",StudArray[ed].grade);
          break;
      }
    }
  // ����� ����������
    c=getch();
    if (!c) c=getch();
    switch(c){
    // �����
      case (72):
        en--;
        if (en<0) en=4;
        break;
    // ����
      case (80):
        en++;
        if (en>4) en=0;
        break;
    // ENTER - �������������� ���� ��� �����
      case (13):
      // ����� ��������
        switch(en) {
          case 0:
            SInput(StudArray[ed].fio,size_FIO+2,34,6);
            break;
          case 1:
            SInput(StudArray[ed].group,size_GROUP+2,34,8);
            break;
          case 2:
            StudArray[ed].avgGrade=GInput(StudArray[ed].grade,size_GRADE+1,34,10);
            break;
        }
      break;
      case(27):
        return;
    }
  }
}

// ���� �������� �������� ����� ��� ����������
float ReadAvgGrade() {
  float avgGrade=0;
  system("cls");
  std::cout << "������� ������� ����: ";
  std::cin >> avgGrade;
  // if avgGrade not float
  return avgGrade;
}

// ����� ��������
int find(int lst) {
// ���������� ��������� �� ������ ��������
  int mNumFIO=MMAX+1,mNumGroup=MMAX+1,mNumAvgGrade=MMAX+1;
  int n;
// �����
  for (n=0;n<StudNum;n++)
  // ���� ������������� �������
    if (compare(StudArray[n].fio,StudArray[MMAX].fio)&&
        compare(StudArray[n].group,StudArray[MMAX].group)&&
        compare(StudArray[n].grade,StudArray[MMAX].grade)) {
    // ������ ��������� �������
      if (mNumFIO>StudArray[n].NumFIO) mNumFIO=StudArray[n].NumFIO;
      if (mNumGroup>StudArray[n].NumGroup) mNumGroup=StudArray[n].NumGroup;
      if (mNumAvgGrade>StudArray[n].NumAvgGrade) mNumAvgGrade=StudArray[n].NumAvgGrade;
  }
// ���������� �������� � ����������� �� ������ ����������
  switch (sort) {
    case (1):
      if (mNumFIO!=0) return mNumFIO;
      break;
    case (2):
      if (mNumGroup!=0) return mNumGroup;
      break;
    case (3):
      if (mNumAvgGrade!=0) return mNumAvgGrade;
      break;
  }
  return lst;
}

// ��������� ������
void scroll() {
  char c;               // ��������� � ���������� ������
  static int menuPOS=1,cursPOS=1; // ������ ������� �� ������ � ��������� �������
  int menuSel;               // ��������� �������� � ����
  int n;                // �������
  float SetAvgGrade=0;    // ������������� ��. ���
// ���� ���������
  for(;;) {
  // ����� ������ �� �����
    output(menuPOS,cursPOS,SetAvgGrade);
  // ���� �������
    c=getch();
    if (!c) c=getch();
  // ��������� �������
    switch (c) {
    // �����
      case (72):
        if (cursPOS>1) cursPOS--; else if (menuPOS>1) menuPOS--;
        break;
    // ����
      case (80):
        if (cursPOS<7) {
          if (cursPOS<(StudNum-menuPOS+1)) cursPOS++;
        } else if (menuPOS<(StudNum-7)) menuPOS++;
        break;
    // ������ ����
      case (27):
        menuSel=menu(30,5," ����������:        "
                          " �� ���             "
                          " �� ������          "
                          " �� ������� ������  "
                          " ����� �� ��������� "
                          "\x0");
      // ���������
        switch (menuSel) {
          case (0):
            cursPOS=menuPOS=1;
            break;
          case (1):
          case (2):
          case (3):
            sort=menuSel;
            break;
          case (4):
            return;
        }
        break;
      // ������ ����
      case (13):
        menuSel=menu(30,5," �������� � ������  "
                          " ������� �� ������  "
                          " �������������      "
                          " ������ �� ��. �����"
                          " ����� �� ����      "
                          "\x0");
        switch(menuSel) {
          case (0):
            if (StudNum<MMAX-1) {
              StudArray[StudNum].fio[0]=0;
              StudArray[StudNum].grade[0]=0;
              StudArray[StudNum].group[0]=0;
              StudNum++;
              edit(StudNum-1);
            }
            index();
            break;
          case (1):
          // �������� ��������
            if (StudNum>1) {
              n=0;
              switch (sort) {
                case (1):
                  while (StudArray[n].NumFIO!=cursPOS+menuPOS-1) n++;
                  break;
                case (2):
                  while (StudArray[n].NumGroup!=cursPOS+menuPOS-1) n++;
                  break;
                case (3):
                  while (StudArray[n].NumAvgGrade!=cursPOS+menuPOS-1) n++;
                  break;
              }
              strcpy(StudArray[n].fio,StudArray[StudNum-1].fio);
              for (int k=0;k<4;k++) StudArray[n].grade[k] = StudArray[StudNum-1].grade[k];
              strcpy(StudArray[n].group,StudArray[StudNum-1].group);
              StudNum--;
              index();
            }
            break;
          case (2):
            n=0;
            switch (sort) {
              case (1):
                while (StudArray[n].NumFIO!=cursPOS+menuPOS-1) n++;
                break;
              case (2):
                while (StudArray[n].NumGroup!=cursPOS+menuPOS-1) n++;
                break;
              case (3):
                while (StudArray[n].NumAvgGrade!=cursPOS+menuPOS-1) n++;
                break;
            }
            edit(n);
            index();
            break;
          case (3):
            SetAvgGrade=ReadAvgGrade();
            break;
          case (4):
            break;
        }
        break;
    }
  }
}

// ������ �������
void load() {
// �������� ����� �� ������
  FILE * f;
  f=fopen("Student.dat","rb");
  if (f==NULL) return;
// ������ ���������� ���������
  fread(&StudNum,1,2,f);
// ������ �������
  fread(StudArray,StudNum,sizeof(Student),f);
// �������� �����
  fclose(f);
}

// ������ �����
void save() {
// �������� ����� �� ������
  FILE * f;
  f=fopen("Student.dat","wb");
  if (f==NULL) {
    printf(" !!! ������ ��� ������ ���� ������ !!! \n");
    return;
  }
// ������ ���������� ��������� � ������
  fwrite(&StudNum,1,2,f);
// ������ �������
  fwrite(StudArray,StudNum,sizeof(Student),f);
// �������� �����
  fclose(f);
}


// �������� ���������
int main() {
// ��������� ��������� ��������
  setlocale(LC_ALL, "RUS");
/*
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
*/
  StudNum=0;
  sort=2;
// ������ �������
  load();
// ���������
  scroll();
  SetColor(7,0);
  system("cls");
// ������ �������
  save();
}

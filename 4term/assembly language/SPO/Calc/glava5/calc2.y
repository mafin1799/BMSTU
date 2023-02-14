%{
/*****************************************
 �������� 㭠�� ����� � ���������� � �⥯���
 ��������� ��ࠡ�⪠ �訡��
 ��������� ॣ���஢� ��६����
******************************************/
#include <math.h>

float mem[26];	/* ���ᨢ ॣ���஢ */
%}

%union{
double data;	/* �᫮��� ���祭�� */
int index;	/* ������ � ���ᨢ� ॣ���஢ */
}

%token <data> DATA
%token <index> VAR
%type <data> wyrag
%right '='
%left '+' '-'
%left '*' '/'
%left '^'
%left UNARYMINUS
%%

spisok :	/* ���� */
  | spisok '\n'	
  | spisok wyrag '\n' 	{ printf("\t%g\n",$2); }
  | spisok error	{
  				resynch();
  				yyclearin;
  				yyerrok;
  			}
  ;
wyrag : DATA 		{ $$=$1; }
  | VAR			{ $$=mem[$1]; }
  | VAR '=' wyrag	{ $$=mem[$1]=$3; }
  | wyrag '+' wyrag	{ $$=$1+$3; }
  | wyrag '-' wyrag	{ $$=$1-$3; }
  | wyrag '*' wyrag	{ $$=$1*$3; }
  | wyrag '/' wyrag	{ 
		  		if($3==0.)
		  			calc_error(1);
		  		$$=$1/$3; 
  			}
  | '(' wyrag ')'	{ $$=$2; }
  | wyrag '^' wyrag	{ $$=pow($1,$3); }
  | '-' wyrag %prec UNARYMINUS { $$=-$2; }
  ;
%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

void fpeerr();


jmp_buf jmp_env;

unsigned int nline=1;	/* ����稪 ��ப */

main()
{
	signal(SIGFPE,fpeerr);
	if(setjmp(jmp_env));
	yyparse();
}

yyerror()
{
	fprintf(stderr,"\n�訡��! ��ப� %u\n(00) ���⠪��᪠� �訡��\n",
						nline);
}

void fpeerr()
{
	calc_error(2);
}

yylex()
{
	int c;
	
	do{
		c=getchar();
	}while(c==' ' || c=='\t');
	
	if(c==EOF)
		return 0;
	if(c=='.' || isdigit(c)){
		ungetc(c,stdin);
		scanf("%lf",&yylval.data);
		return DATA;
	}
	
	if(islower(c)){
		yylval.index=c-'a';
		return VAR;
	}
	
	if(c=='\n')
		nline++;
	
	return c;
}

resynch()
{
	int c;
	
	do{
		c=getchar();
	}while(c!='\n');

	ungetc(c,stdin);
}

char *ms_calc_error[]={
/* 0 */ "",
/* 1 */ "������� �� 0",
/* 2 */ "��९������� ����⢥�����"
};

calc_error(num)
int num;
{
	fprintf(stderr,"\n�訡��! ��ப� %u\n(%02d) %s\n",
						nline,num,ms_calc_error[num]);
	longjmp(jmp_env,1);
}

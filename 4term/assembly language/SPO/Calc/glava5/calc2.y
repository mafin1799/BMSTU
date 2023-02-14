%{
/*****************************************
 Добавлен унарный минус и возведение в степень
 Добавлена обработка ошибок
 Добавлены регистровые переменные
******************************************/
#include <math.h>

float mem[26];	/* массив регистров */
%}

%union{
double data;	/* числовое значение */
int index;	/* индекс в массиве регистров */
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

spisok :	/* пусто */
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

unsigned int nline=1;	/* счётчик строк */

main()
{
	signal(SIGFPE,fpeerr);
	if(setjmp(jmp_env));
	yyparse();
}

yyerror()
{
	fprintf(stderr,"\nОшибка! Строка %u\n(00) Синтаксическая ошибка\n",
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
/* 1 */ "Деление на 0",
/* 2 */ "Переполнение вещественного"
};

calc_error(num)
int num;
{
	fprintf(stderr,"\nОшибка! Строка %u\n(%02d) %s\n",
						nline,num,ms_calc_error[num]);
	longjmp(jmp_env,1);
}

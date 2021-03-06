/* hp --- reverse Polish notation calculator program */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "st.parse.h"

#define MAXSTACK	100
#define MAXLINE		102
#define TRUE		1
#define FALSE		0
#define NEWLINE		'\n'
#define EOS		'\0'

double stack [MAXSTACK + 1];
int scanptr = -1;
int sp = 0;
int state;
int symbol;
char line [MAXLINE];

extern char *strcpy();

main(argc, argv)
int argc;
char **argv;
{
	int i, l;
	int sound();

	if (argc > 1)
	{
		l = 0;
		/* concatenate args into one line for getsym() to use... */
		for (i = 1; argv[i] != NULL; i++)
		{
			(void) strcpy (& line[l], argv[i]);
			l += strlen (argv[i]);
			line [l] = ' ';
			l++;
		}
		scanptr = -1;
		getsym();
		expression (& state);
		if (sound (1))
			printf ("%1.1lf\n", stack [sp]);
	}
	else
		while (fgets (line, sizeof line, stdin) != NULL)
		{
			scanptr = -1;
			getsym();
			expression (& state);
		}
}

/* ctod --- do atof, but increment pointer into the line buffer */

double ctod (text, indx)
char text[];
int *indx;
{
	double result, atof();
	char buf[MAXLINE];
	int i = 0;

	while (isdigit (text[*indx]))
	{
		buf[i++] = text[*indx];
		(*indx)++;
	}

	if (text[*indx] == '.')
	{
		buf[i++] = '.';
		(*indx)++;
	}
	
	while (isdigit (text[*indx]))
	{
		buf[i++] = text[*indx];
		(*indx)++;
	}

	if (text[*indx] == 'e' ||  text[*indx] == 'E')
	{
		buf[i++] = text[*indx];
		(*indx)++;
	
		if (text[*indx] == '-' || text[*indx] == '+')
		{
			buf[i++] = text[*indx];
			(*indx)++;
		}

		while (isdigit (text[*indx]))
		{
			buf[i++] = text[*indx];
			(*indx)++;
		}
	}

	buf[i] = '\0';

	result = atof (buf);
	return (result);
}

/* fmod --- do floating modulus */

double fmod (x, y)
double x, y;
{
	extern double modf();
	extern double fabs();
	double f;
	int flag = 0;
	double ipart;

	if (y == 0.0)
		return (x);

	flag = (x < 0.0);
	x = fabs (x);
	y = fabs (y);
	(void) modf (x / y, & ipart);
	f = x - y * ipart;
	return (flag ? -f : f);
}

#include "st.parse.c"

/* push --- push one item onto the stack */

#define remark(msg)	fprintf (stderr, "%s\n", msg)

push (stuff)
double stuff;
{
	if (sp > MAXSTACK)
	{
		remark ("stack overflow");
		state = FAILURE;
	}
	else
	{
		sp++;
		stack [sp] = stuff;
	}
}



/* sound --- sound out the depth of the stack */

int sound (depth)
int depth;
{
	if (sp < depth)
	{
		remark ("stack underflow");
		state = FAILURE;	/* to insure immediate exit from expression */
		return (FALSE);
	}
	else
		return (TRUE);
}



/* getsym --- get next character from input line */

/*
 * we cheat a little here, so that substitutes for things that would
 * otherwise be shell metacharacters can be used...
 */

getsym()
{
	scanptr++;
	if ((symbol = line [scanptr]) == 'x' || symbol == 'X')
		symbol = '*';
	else if (symbol == ':')
		symbol = '^';
}

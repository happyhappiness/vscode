static int
yylex (yylval, cookie)
     YYSTYPE *yylval;
     void *cookie;
{
  register unsigned char c;
  register char *p;
  char buff[20];
  int Count;
  int sign;

  for (;;)
    {
      while (ISSPACE ((unsigned char) *context->yyInput))
	context->yyInput++;

      if (ISDIGIT (c = *context->yyInput) || c == '-' || c == '+')
	{
	  if (c == '-' || c == '+')
	    {
	      sign = c == '-' ? -1 : 1;
	      if (!ISDIGIT (*++context->yyInput))
		/* skip the '-' sign */
		continue;
	    }
	  else
	    sign = 0;
	  for (yylval->Number = 0; ISDIGIT (c = *context->yyInput++);)
	    yylval->Number = 10 * yylval->Number + c - '0';
	  context->yyInput--;
	  if (sign < 0)
	    yylval->Number = -yylval->Number;
	  return sign ? tSNUMBER : tUNUMBER;
	}
      if (ISALPHA (c))
	{
	  for (p = buff; (c = *context->yyInput++, ISALPHA (c)) || c == '.';)
	    if (p < &buff[sizeof buff - 1])
	      *p++ = c;
	  *p = '\0';
	  context->yyInput--;
	  return LookupWord (yylval, buff);
	}
      if (c != '(')
	return *context->yyInput++;
      Count = 0;
      do
	{
	  c = *context->yyInput++;
	  if (c == '\0')
	    return c;
	  if (c == '(')
	    Count++;
	  else if (c == ')')
	    Count--;
	}
      while (Count > 0);
    }
}
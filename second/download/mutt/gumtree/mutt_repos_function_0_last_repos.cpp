static int dopr (char *buffer, size_t maxlen, const char *format, va_list args)
{
  char ch;
  long value;
  long double fvalue;
  char *strvalue;
  int min;
  int max;
  int state;
  int flags;
  int cflags;
  size_t currlen;
  
  state = DP_S_DEFAULT;
  currlen = flags = cflags = min = 0;
  max = -1;
  ch = *format++;

  while (state != DP_S_DONE)
  {
    if (ch == '\0')
      state = DP_S_DONE;

    switch(state) 
    {
    case DP_S_DEFAULT:
      if (ch == '%') 
	state = DP_S_FLAGS;
      else 
	dopr_outch (buffer, &currlen, maxlen, ch);
      ch = *format++;
      break;
    case DP_S_FLAGS:
      switch (ch) 
      {
      case '-':
	flags |= DP_F_MINUS;
        ch = *format++;
	break;
      case '+':
	flags |= DP_F_PLUS;
        ch = *format++;
	break;
      case ' ':
	flags |= DP_F_SPACE;
        ch = *format++;
	break;
      case '#':
	flags |= DP_F_NUM;
        ch = *format++;
	break;
      case '0':
	flags |= DP_F_ZERO;
        ch = *format++;
	break;
      default:
	state = DP_S_MIN;
	break;
      }
      break;
    case DP_S_MIN:
      if (isdigit((unsigned char)ch)) 
      {
	min = 10*min + char_to_int (ch);
	ch = *format++;
      } 
      else if (ch == '*') 
      {
	min = va_arg (args, int);
	ch = *format++;
	state = DP_S_DOT;
      } 
      else 
	state = DP_S_DOT;
      break;
    case DP_S_DOT:
      if (ch == '.') 
      {
	state = DP_S_MAX;
	ch = *format++;
      } 
      else 
	state = DP_S_MOD;
      break;
    case DP_S_MAX:
      if (isdigit((unsigned char)ch)) 
      {
	if (max < 0)
	  max = 0;
	max = 10*max + char_to_int (ch);
	ch = *format++;
      } 
      else if (ch == '*') 
      {
	max = va_arg (args, int);
	ch = *format++;
	state = DP_S_MOD;
      } 
      else 
	state = DP_S_MOD;
      break;
    case DP_S_MOD:
      switch (ch) 
      {
      case 'h':
	cflags = DP_C_SHORT;
	ch = *format++;
	break;
      case 'l':
	cflags = DP_C_LONG;
	ch = *format++;
	if (ch == 'l')
	{
	  cflags = DP_C_LONGLONG;
	  ch = *format++;
	}
	break;
      case 'L':
	cflags = DP_C_LDOUBLE;
	ch = *format++;
	break;
      default:
	break;
      }
      state = DP_S_CONV;
      break;
    case DP_S_CONV:
      switch (ch) 
      {
      case 'd':
      case 'i':
	if (cflags == DP_C_SHORT) 
	  value = va_arg (args, short int);
	else if (cflags == DP_C_LONG)
	  value = va_arg (args, long int);
	else if (cflags == DP_C_LONGLONG)
	  value = va_arg (args, long long int);
	else
	  value = va_arg (args, int);
	fmtint (buffer, &currlen, maxlen, value, 10, min, max, flags);
	break;
      case 'o':
	flags |= DP_F_UNSIGNED;
	if (cflags == DP_C_SHORT)
	  value = va_arg (args, unsigned short int);
	else if (cflags == DP_C_LONG)
	  value = va_arg (args, unsigned long int);
	else if (cflags == DP_C_LONGLONG)
	  value = va_arg (args, unsigned long long int);
	else
	  value = va_arg (args, unsigned int);
	fmtint (buffer, &currlen, maxlen, value, 8, min, max, flags);
	break;
      case 'u':
	flags |= DP_F_UNSIGNED;
	if (cflags == DP_C_SHORT)
	  value = va_arg (args, unsigned short int);
	else if (cflags == DP_C_LONG)
	  value = va_arg (args, unsigned long int);
	else if (cflags == DP_C_LONGLONG)
	  value = va_arg (args, unsigned long long int);
	else
	  value = va_arg (args, unsigned int);
	fmtint (buffer, &currlen, maxlen, value, 10, min, max, flags);
	break;
      case 'X':
	flags |= DP_F_UP;
      case 'x':
	flags |= DP_F_UNSIGNED;
	if (cflags == DP_C_SHORT)
	  value = va_arg (args, unsigned short int);
	else if (cflags == DP_C_LONG)
	  value = va_arg (args, unsigned long int);
	else if (cflags == DP_C_LONGLONG)
	  value = va_arg (args, unsigned long long int);
	else
	  value = va_arg (args, unsigned int);
	fmtint (buffer, &currlen, maxlen, value, 16, min, max, flags);
	break;
      case 'f':
	if (cflags == DP_C_LDOUBLE)
	  fvalue = va_arg (args, long double);
	else
	  fvalue = va_arg (args, double);
	/* um, floating point? */
	fmtfp (buffer, &currlen, maxlen, fvalue, min, max, flags);
	break;
      case 'E':
	flags |= DP_F_UP;
      case 'e':
	if (cflags == DP_C_LDOUBLE)
	  fvalue = va_arg (args, long double);
	else
	  fvalue = va_arg (args, double);
	break;
      case 'G':
	flags |= DP_F_UP;
      case 'g':
	if (cflags == DP_C_LDOUBLE)
	  fvalue = va_arg (args, long double);
	else
	  fvalue = va_arg (args, double);
	break;
      case 'c':
	dopr_outch (buffer, &currlen, maxlen, va_arg (args, int));
	break;
      case 's':
	strvalue = va_arg (args, char *);
	fmtstr (buffer, &currlen, maxlen, strvalue, flags, min, max);
	break;
      case 'p':
	flags |= DP_F_UNSIGNED;
	strvalue = va_arg (args, void *);
	fmtint (buffer, &currlen, maxlen, (long) strvalue, 16, min, max, flags);
	break;
      case 'n':
	if (cflags == DP_C_SHORT) 
	{
	  short int *num;
	  num = va_arg (args, short int *);
	  *num = currlen;
        } 
	else if (cflags == DP_C_LONG) 
	{
	  long int *num;
	  num = va_arg (args, long int *);
	  *num = currlen;
        } 
	else if (cflags == DP_C_LONGLONG) 
	{
	  long long int *num;
	  num = va_arg (args, long long int *);
	  *num = currlen;
        } 
	else 
	{
	  int *num;
	  num = va_arg (args, int *);
	  *num = currlen;
        }
	break;
      case '%':
	dopr_outch (buffer, &currlen, maxlen, ch);
	break;
      case 'w':
	/* not supported yet, treat as next char */
	ch = *format++;
	break;
      default:
	/* Unknown, skip */
	break;
      }
      ch = *format++;
      state = DP_S_DEFAULT;
      flags = cflags = min = 0;
      max = -1;
      break;
    case DP_S_DONE:
      break;
    default:
      /* hmm? */
      break; /* some picky compilers need this */
    }
  }
  if (currlen < maxlen - 1) 
    buffer[currlen] = '\0';
  else 
    buffer[maxlen - 1] = '\0';

  return (int)currlen;
}
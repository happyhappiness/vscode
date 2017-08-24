{
  const numericARG *argn = (const numericARG *)argp;
  double low          = argn->low;
  double high         = argn->high;
  int prec            = argn->precision;
  unsigned char *bp   = (unsigned char *)field_buffer(field,0);
  char *s             = (char *)bp;
  double val          = 0.0;
  char buf[64];

  while(*bp && *bp==' ') bp++;
  if (*bp)
    {
      if (*bp=='-' || *bp=='+')
	bp++;
      while(*bp)
	{
	  if (!isdigit(*bp)) break;
	  bp++;
	}
      if (*bp==(
#if HAVE_LOCALE_H
		(L && L->decimal_point) ? *(L->decimal_point) :
#endif
		'.'))
	{
	  bp++;
	  while(*bp)
	    {
	      if (!isdigit(*bp)) break;
	      bp++;
	    }
	}
      while(*bp && *bp==' ') bp++;
      if (*bp=='\0')
	{
	  val = atof(s);
	  if (low<high)
	    {
	      if (val<low || val>high) return FALSE;
	    }
	  sprintf(buf,"%.*f",(prec>0?prec:0),val);
	  set_field_buffer(field,0,buf);
	  return TRUE;
	}
    }
  return FALSE;
}
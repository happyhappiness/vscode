static bool Check_Integer_Field(FIELD * field, const void * argp)
{
  const integerARG *argi = (const integerARG *)argp;
  long low          = argi->low;
  long high         = argi->high;
  int prec          = argi->precision;
  unsigned char *bp = (unsigned char *)field_buffer(field,0);
  char *s           = (char *)bp;
  long val;
  char buf[100];

  while( *bp && *bp==' ') bp++;
  if (*bp)
    {
      if (*bp=='-') bp++;
      while (*bp)
	{
	  if (!isdigit(*bp)) break;
	  bp++;
	}
      while(*bp && *bp==' ') bp++;
      if (*bp=='\0')
	{
	  val = atol(s);
	  if (low<high)
	    {
	      if (val<low || val>high) return FALSE;
	    }
	  sprintf(buf,"%.*ld",(prec>0?prec:0),val);
	  set_field_buffer(field,0,buf);
	  return TRUE;
	}
    }
  return FALSE;
}
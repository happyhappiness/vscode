int rfc1524_expand_command (BODY *a, char *filename, char *_type,
    char *command, int clen)
{
  int x=0,y=0;
  int needspipe = TRUE;
  char buf[LONG_STRING];
  char type[LONG_STRING];
  
  strfcpy (type, _type, sizeof (type));
  
  if (option (OPTMAILCAPSANITIZE))
    mutt_sanitize_filename (type, 0);

  while (x < clen - 1 && command[x] && y < sizeof (buf) - 1)
  {
    if (command[x] == '\\')
    {
      x++;
      buf[y++] = command[x++];
    }
    else if (command[x] == '%') 
    {
      x++;
      if (command[x] == '{') 
      {
	char param[STRING];
	char pvalue[STRING];
	char *_pvalue;
	int z = 0;

	x++;
	while (command[x] && command[x] != '}' && z < sizeof (param) - 1)
	  param[z++] = command[x++];
	param[z] = '\0';
	
	_pvalue = mutt_get_parameter (param, a->parameter);
	strfcpy (pvalue, NONULL(_pvalue), sizeof (pvalue));
	if (option (OPTMAILCAPSANITIZE))
	  mutt_sanitize_filename (pvalue, 0);
	
	y += mutt_quote_filename (buf + y, sizeof (buf) - y, pvalue);
      }
      else if (command[x] == 's' && filename != NULL)
      {
	y += mutt_quote_filename (buf + y, sizeof (buf) - y, filename);
	needspipe = FALSE;
      }
      else if (command[x] == 't')
      {
	y += mutt_quote_filename (buf + y, sizeof (buf) - y, type);
      }
      x++;
    }
    else
      buf[y++] = command[x++];
  }
  buf[y] = '\0';
  strfcpy (command, buf, clen);

  return needspipe;
}
static int
Curl_formadd_convert(struct curl_forms * forms,
                     int formx, int lengthx, unsigned int ccsid)

{
  int l;
  char * cp;
  char * cp2;

  if(formx < 0 || !forms[formx].value)
    return 0;

  if(lengthx >= 0)
    l = (int) forms[lengthx].value;
  else
    l = strlen(forms[formx].value) + 1;

  cp = malloc(MAX_CONV_EXPANSION * l);

  if(!cp)
    return -1;

  l = convert(cp, MAX_CONV_EXPANSION * l, ASCII_CCSID,
              forms[formx].value, l, ccsid);

  if(l < 0) {
    free(cp);
    return -1;
    }

  cp2 = realloc(cp, l);         /* Shorten buffer to the string size. */

  if(cp2)
    cp = cp2;

  forms[formx].value = cp;

  if(lengthx >= 0)
    forms[lengthx].value = (char *) l;  /* Update length after conversion. */

  return l;
}
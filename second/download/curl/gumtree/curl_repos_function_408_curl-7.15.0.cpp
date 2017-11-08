char *Curl_FormBoundary(void)
{
  char *retstring;
  static int randomizer;   /* this is just so that two boundaries within
                              the same form won't be identical */
  size_t i;

  static const char table16[]="abcdef0123456789";

  retstring = (char *)malloc(BOUNDARY_LENGTH+1);

  if(!retstring)
    return NULL; /* failed */

  srand((unsigned int)time(NULL)+randomizer++); /* seed */

  strcpy(retstring, "----------------------------");

  for(i=strlen(retstring); i<BOUNDARY_LENGTH; i++)
    retstring[i] = table16[rand()%16];

  /* 28 dashes and 12 hexadecimal digits makes 12^16 (184884258895036416)
     combinations */
  retstring[BOUNDARY_LENGTH]=0; /* zero terminate */

  return retstring;
}
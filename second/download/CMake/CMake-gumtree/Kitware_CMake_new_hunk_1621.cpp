

#endif



#else  /* CURL_DISABLE_HTTP */

CURLFORMcode curl_formadd(struct curl_httppost **httppost,

                          struct curl_httppost **last_post,

                          ...)

{

  (void)httppost;

  (void)last_post;

  return CURL_FORMADD_DISABLED;

}



void curl_formfree(struct curl_httppost *form)

{

  (void)form;

  /* does nothing HTTP is disabled */

}



#endif  /* CURL_DISABLE_HTTP */



/*

 * Curl_FormBoundary() creates a suitable boundary string and returns an

 * allocated one. This is also used by SSL-code so it must be present even

 * if HTTP is disabled!

 */

char *Curl_FormBoundary(void)

{

  char *retstring;

  static int randomizer=0; /* this is just so that two boundaries within

                              the same form won't be identical */

  size_t i;



  static char table16[]="abcdef0123456789";



  retstring = (char *)malloc(BOUNDARY_LENGTH+1);



  if(!retstring)

    return NULL; /* failed */



  srand(time(NULL)+randomizer++); /* seed */



  strcpy(retstring, "----------------------------");



  for(i=strlen(retstring); i<BOUNDARY_LENGTH; i++)

    retstring[i] = table16[rand()%16];



  /* 28 dashes and 12 hexadecimal digits makes 12^16 (184884258895036416)

     combinations */

  retstring[BOUNDARY_LENGTH]=0; /* zero terminate */



  return retstring;

}

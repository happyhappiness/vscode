  return result;

}



static int AddFormData(struct FormData **formp,

                       const void *line,

                       long length)

{

  struct FormData *newform = (struct FormData *)

    malloc(sizeof(struct FormData));

  newform->next = NULL;



  /* we make it easier for plain strings: */

  if(!length)

    length = (long)strlen((char *)line);



  newform->line = (char *)malloc(length+1);

  memcpy(newform->line, line, length);

  newform->length = length;

  newform->line[length]=0; /* zero terminate for easier debugging */

  

  if(*formp) {

    (*formp)->next = newform;

    *formp = newform;

  }

  else

    *formp = newform;



  return length;

}





static int AddFormDataf(struct FormData **formp,

                        const char *fmt, ...)

{

  char s[4096];

  va_list ap;

  va_start(ap, fmt);

  vsprintf(s, fmt, ap);

  va_end(ap);



  return AddFormData(formp, s, 0);

}





char *Curl_FormBoundary(void)

{

  char *retstring;

  static int randomizer=0; /* this is just so that two boundaries within

                              the same form won't be identical */

  int i;



  static char table62[]=

    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";



  retstring = (char *)malloc(BOUNDARY_LENGTH);



  if(!retstring)

    return NULL; /* failed */



  srand((unsigned int)(time(NULL)+randomizer++)); /* seed */



  strcpy(retstring, "curl"); /* bonus commercials 8*) */



  for(i=4; i<(BOUNDARY_LENGTH-1); i++) {

    retstring[i] = table62[rand()%62];

  }

  retstring[BOUNDARY_LENGTH-1]=0; /* zero terminate */



  return retstring;

}



/* Used from http.c, this cleans a built FormData linked list */ 

void Curl_formclean(struct FormData *form)

{

  struct FormData *next;



  do {

    next=form->next;  /* the following form line */

    free(form->line); /* free the line */

    free(form);       /* free the struct */

  

  } while((form=next)); /* continue */

}



/* external function to free up a whole form post chain */

void curl_formfree(struct curl_httppost *form)

{

  struct curl_httppost *next;


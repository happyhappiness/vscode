  return result;

}



/*

 * AddFormData() adds a chunk of data to the FormData linked list.

 *

 * size is incremented by the chunk length, unless it is NULL

 */

static CURLcode AddFormData(struct FormData **formp,

                            enum formtype type,

                            const void *line,

                            size_t length,

                            curl_off_t *size)

{

  struct FormData *newform = (struct FormData *)

    malloc(sizeof(struct FormData));

  if (!newform)

    return CURLE_OUT_OF_MEMORY;

  newform->next = NULL;



  /* we make it easier for plain strings: */

  if(!length)

    length = strlen((char *)line);



  newform->line = (char *)malloc(length+1);

  if (!newform->line) {

    free(newform);

    return CURLE_OUT_OF_MEMORY;

  }

  memcpy(newform->line, line, length);

  newform->length = length;

  newform->line[length]=0; /* zero terminate for easier debugging */

  newform->type = type;



  if(*formp) {

    (*formp)->next = newform;

    *formp = newform;

  }

  else

    *formp = newform;



  if (size) {

    if(type == FORM_DATA)

      *size += length;

    else {

      /* Since this is a file to be uploaded here, add the size of the actual

         file */

      if(!strequal("-", newform->line)) {

        struct stat file;

        if(!stat(newform->line, &file)) {

          *size += file.st_size;

        }

      }

    }

  }

  return CURLE_OK;

}



/*

 * AddFormDataf() adds printf()-style formatted data to the formdata chain.

 */



static CURLcode AddFormDataf(struct FormData **formp,

                             curl_off_t *size,

                             const char *fmt, ...)

{

  char s[4096];

  va_list ap;

  va_start(ap, fmt);

  vsnprintf(s, sizeof(s), fmt, ap);

  va_end(ap);



  return AddFormData(formp, FORM_DATA, s, 0, size);

}



/*

 * Curl_formclean() is used from http.c, this cleans a built FormData linked

 * list

 */

void Curl_formclean(struct FormData *form)

{

  struct FormData *next;



  if(!form)

    return;



  do {

    next=form->next;  /* the following form line */

    free(form->line); /* free the line */

    free(form);       /* free the struct */



  } while((form=next)); /* continue */

}



/*

 * curl_formfree() is an external function to free up a whole form post

 * chain

 */

void curl_formfree(struct curl_httppost *form)

{

  struct curl_httppost *next;


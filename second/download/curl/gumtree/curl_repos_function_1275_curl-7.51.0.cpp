static CURLcode AddFormData(struct FormData **formp,
                            enum formtype type,
                            const void *line,
                            curl_off_t length,
                            curl_off_t *size)
{
  struct FormData *newform;
  char *alloc2 = NULL;
  CURLcode result = CURLE_OK;
  if(length < 0 || (size && *size < 0))
    return CURLE_BAD_FUNCTION_ARGUMENT;

  newform = malloc(sizeof(struct FormData));
  if(!newform)
    return CURLE_OUT_OF_MEMORY;
  newform->next = NULL;

  if(type <= FORM_CONTENT) {
    /* we make it easier for plain strings: */
    if(!length)
      length = strlen((char *)line);
#if (SIZEOF_SIZE_T < CURL_SIZEOF_CURL_OFF_T)
    else if(length >= (curl_off_t)(size_t)-1) {
      result = CURLE_BAD_FUNCTION_ARGUMENT;
      goto error;
    }
#endif
    if(type != FORM_DATAMEM) {
      newform->line = malloc((size_t)length+1);
      if(!newform->line) {
        result = CURLE_OUT_OF_MEMORY;
        goto error;
      }
      alloc2 = newform->line;
      memcpy(newform->line, line, (size_t)length);

      /* zero terminate for easier debugging */
      newform->line[(size_t)length]=0;
    }
    else {
      newform->line = (char *)line;
      type = FORM_DATA; /* in all other aspects this is just FORM_DATA */
    }
    newform->length = (size_t)length;
  }
  else
    /* For callbacks and files we don't have any actual data so we just keep a
       pointer to whatever this points to */
    newform->line = (char *)line;

  newform->type = type;

  if(size) {
    if(type != FORM_FILE)
      /* for static content as well as callback data we add the size given
         as input argument */
      *size += length;
    else {
      /* Since this is a file to be uploaded here, add the size of the actual
         file */
      if(strcmp("-", newform->line)) {
        struct_stat file;
        if(!stat(newform->line, &file) && !S_ISDIR(file.st_mode))
          *size += filesize(newform->line, file);
        else {
          result = CURLE_BAD_FUNCTION_ARGUMENT;
          goto error;
        }
      }
    }
  }

  if(*formp) {
    (*formp)->next = newform;
    *formp = newform;
  }
  else
    *formp = newform;

  return CURLE_OK;
  error:
  if(newform)
    free(newform);
  if(alloc2)
    free(alloc2);
  return result;
}
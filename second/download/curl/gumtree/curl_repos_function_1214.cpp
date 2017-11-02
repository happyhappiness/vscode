static CURLcode AddFormData(struct FormData **formp,
                            enum formtype type,
                            const void *line,
                            size_t length,
                            curl_off_t *size)
{
  struct FormData *newform = malloc(sizeof(struct FormData));
  if(!newform)
    return CURLE_OUT_OF_MEMORY;
  newform->next = NULL;

  if(type <= FORM_CONTENT) {
    /* we make it easier for plain strings: */
    if(!length)
      length = strlen((char *)line);

    newform->line = malloc(length+1);
    if(!newform->line) {
      free(newform);
      return CURLE_OUT_OF_MEMORY;
    }
    memcpy(newform->line, line, length);
    newform->length = length;
    newform->line[length]=0; /* zero terminate for easier debugging */
  }
  else
    /* For callbacks and files we don't have any actual data so we just keep a
       pointer to whatever this points to */
    newform->line = (char *)line;

  newform->type = type;

  if(*formp) {
    (*formp)->next = newform;
    *formp = newform;
  }
  else
    *formp = newform;

  if(size) {
    if(type != FORM_FILE)
      /* for static content as well as callback data we add the size given
         as input argument */
      *size += length;
    else {
      /* Since this is a file to be uploaded here, add the size of the actual
         file */
      if(!strequal("-", newform->line)) {
        struct_stat file;
        if(!stat(newform->line, &file) && !S_ISDIR(file.st_mode))
          *size += filesize(newform->line, file);
        else
          return CURLE_BAD_FUNCTION_ARGUMENT;
      }
    }
  }
  return CURLE_OK;
}
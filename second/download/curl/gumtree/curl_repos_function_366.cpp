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
        struct_stat file;
        if(!stat(newform->line, &file)) {
          *size += file.st_size;
        }
      }
    }
  }
  return CURLE_OK;
}
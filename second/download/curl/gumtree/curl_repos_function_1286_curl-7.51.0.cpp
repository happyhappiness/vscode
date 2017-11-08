static size_t readfromfile(struct Form *form, char *buffer,
                           size_t size)
{
  size_t nread;
  bool callback = (form->data->type == FORM_CALLBACK)?TRUE:FALSE;

  if(callback) {
    if(form->fread_func == ZERO_NULL)
      return 0;
    else
      nread = form->fread_func(buffer, 1, size, form->data->line);
  }
  else {
    if(!form->fp) {
      /* this file hasn't yet been opened */
      form->fp = fopen_read(form->data->line, "rb"); /* b is for binary */
      if(!form->fp)
        return (size_t)-1; /* failure */
    }
    nread = fread(buffer, 1, size, form->fp);
  }
  if(!nread) {
    /* this is the last chunk from the file, move on */
    if(form->fp) {
      fclose(form->fp);
      form->fp = NULL;
    }
    form->data = form->data->next;
  }

  return nread;
}
static size_t readfromfile(struct Form *form, char *buffer, size_t size)
{
  size_t nread;
  if(!form->fp) {
    /* this file hasn't yet been opened */
    form->fp = fopen(form->data->line, "rb"); /* b is for binary */
    if(!form->fp)
      return -1; /* failure */
  }
  nread = fread(buffer, 1, size, form->fp);

  if(nread != size) {
    /* this is the last chunk form the file, move on */
    fclose(form->fp);
    form->fp = NULL;
    form->data = form->data->next;
  }

  return nread;
}
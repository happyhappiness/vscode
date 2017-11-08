char *Curl_formpostheader(void *formp, size_t *len)
{
  char *header;
  struct Form *form=(struct Form *)formp;

  if(!form->data)
    return NULL; /* nothing, ERROR! */

  header = form->data->line;
  *len = form->data->length;

  form->data = form->data->next; /* advance */

  return header;
}
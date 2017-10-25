int FormReader(char *buffer,
	       size_t size,
	       size_t nitems,
	       FILE *mydata)
{
  struct Form *form;
  int wantedsize;
  int gotsize;

  form=(struct Form *)mydata;

  wantedsize = size * nitems;

  if(!form->data)
    return -1; /* nothing, error, empty */

  do {
  
    if( (form->data->length - form->sent ) > wantedsize ) {

      memcpy(buffer, form->data->line + form->sent, wantedsize);

      form->sent += wantedsize;

      return wantedsize;
    }

    memcpy(buffer,
           form->data->line + form->sent,
           gotsize = (form->data->length - form->sent) );

    form->sent = 0;

    form->data = form->data->next; /* advance */

  } while(!gotsize && form->data);
  /* If we got an empty line and we have more data, we proceed to the next
     line immediately to avoid returning zero before we've reached the end.
     This is the bug reported November 22 1999 on curl 6.3. (Daniel) */

  return gotsize;
}
int FormInit(struct Form *form, struct FormData *formdata )
{
  if(!formdata)
    return 1; /* error */

#if 0  
  struct FormData *lastnode=formdata;

  /* find the last node in the list */
  while(lastnode->next) {
    lastnode = lastnode->next;
  }

  /* Now, make sure that we'll send a nice terminating sequence at the end
   * of the post. We *DONT* add this string to the size of the data since this
   * is actually AFTER the data. */
  AddFormDataf(&lastnode, "\r\n\r\n");
#endif
  form->data = formdata;
  form->sent = 0;

  return 0;
}
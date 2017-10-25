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
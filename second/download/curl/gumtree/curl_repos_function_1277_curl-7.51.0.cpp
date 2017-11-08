void Curl_formclean(struct FormData **form_ptr)
{
  struct FormData *next, *form;

  form = *form_ptr;
  if(!form)
    return;

  do {
    next=form->next;  /* the following form line */
    if(form->type <= FORM_CONTENT)
      free(form->line); /* free the line */
    free(form);       /* free the struct */

  } while((form = next) != NULL); /* continue */

  *form_ptr = NULL;
}
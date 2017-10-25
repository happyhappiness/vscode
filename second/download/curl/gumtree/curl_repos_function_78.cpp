void FormFree(struct FormData *form)
{
  struct FormData *next;
  do {
    next=form->next;  /* the following form line */
    free(form->line); /* free the line */
    free(form);       /* free the struct */

  } while((form=next)); /* continue */
}
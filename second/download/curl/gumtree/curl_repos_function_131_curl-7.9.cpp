void curl_formfree(struct HttpPost *form)
{
  struct HttpPost *next;

  if(!form)
    /* no form to free, just get out of this */
    return;

  do {
    next=form->next;  /* the following form line */

    /* recurse to sub-contents */
    if(form->more)
      curl_formfree(form->more);

    if( !(form->flags & HTTPPOST_PTRNAME) && form->name)
      free(form->name); /* free the name */
    if( !(form->flags & HTTPPOST_PTRCONTENTS) && form->contents)
      free(form->contents); /* free the contents */
    if(form->contenttype)
      free(form->contenttype); /* free the content type */
    free(form);       /* free the struct */

  } while((form=next)); /* continue */
}
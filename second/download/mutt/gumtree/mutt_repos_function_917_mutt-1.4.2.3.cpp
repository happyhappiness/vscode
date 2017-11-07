void mutt_free_body (BODY **p)
{
  BODY *a = *p, *b;

  while (a)
  {
    b = a;
    a = a->next; 

    if (b->parameter)
      mutt_free_parameter (&b->parameter);
    if (b->unlink && b->filename)
      unlink (b->filename);
    safe_free ((void **) &b->filename);
    safe_free ((void **) &b->content);
    safe_free ((void **) &b->xtype);
    safe_free ((void **) &b->subtype);
    safe_free ((void **) &b->description);
    safe_free ((void **) &b->form_name);

    if (b->hdr)
    {
      /* Don't free twice (b->hdr->content = b->parts) */
      b->hdr->content = NULL;
      mutt_free_header(&b->hdr);
    }

    if (b->parts)
      mutt_free_body (&b->parts);

    safe_free ((void **) &b);
  }

  *p = 0;
}
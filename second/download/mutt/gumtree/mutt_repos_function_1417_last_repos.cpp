void mutt_free_body (BODY **p)
{
  BODY *a = *p, *b;

  while (a)
  {
    b = a;
    a = a->next; 

    if (b->parameter)
      mutt_free_parameter (&b->parameter);
    if (b->filename)
    {
      if (b->unlink)
	unlink (b->filename);
      dprint (1, (debugfile, "mutt_free_body: %sunlinking %s.\n",
	    b->unlink ? "" : "not ", b->filename));
    }

    FREE (&b->filename);
    FREE (&b->d_filename);
    FREE (&b->charset);
    FREE (&b->content);
    FREE (&b->xtype);
    FREE (&b->subtype);
    FREE (&b->description);
    FREE (&b->form_name);

    if (b->hdr)
    {
      /* Don't free twice (b->hdr->content = b->parts) */
      b->hdr->content = NULL;
      mutt_free_header(&b->hdr);
    }

    if (b->parts)
      mutt_free_body (&b->parts);

    FREE (&b);
  }

  *p = 0;
}
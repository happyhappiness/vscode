static void mutt_gen_compose_attach_list (ATTACH_CONTEXT *actx,
                                          BODY *m,
                                          int parent_type,
                                          int level)
{
  ATTACHPTR *new;

  for (; m; m = m->next)
  {
    if (m->type == TYPEMULTIPART && m->parts
        && (!(WithCrypto & APPLICATION_PGP) || !mutt_is_multipart_encrypted(m))
	)
    {
      mutt_gen_compose_attach_list (actx, m->parts, m->type, level);
    }
    else
    {
      new = (ATTACHPTR *) safe_calloc (1, sizeof (ATTACHPTR));
      mutt_actx_add_attach (actx, new);
      new->content = m;
      m->aptr = new;
      new->parent_type = parent_type;
      new->level = level;

      /* We don't support multipart messages in the compose menu yet */
    }
  }
}
ATTACHPTR **mutt_gen_attach_list (BODY *m,
				  int parent_type,
				  ATTACHPTR **idx,
				  short *idxlen,
				  short *idxmax,
				  int level,
				  int compose)
{
  ATTACHPTR *new;
  int i;
  
  for (; m; m = m->next)
  {
    if (*idxlen == *idxmax)
    {
      safe_realloc (&idx, sizeof (ATTACHPTR *) * ((*idxmax) += 5));
      for (i = *idxlen; i < *idxmax; i++)
	idx[i] = NULL;
    }

    if (m->type == TYPEMULTIPART && m->parts
	&& (compose || (parent_type == -1 && ascii_strcasecmp ("alternative", m->subtype)))
        && (!(WithCrypto & APPLICATION_PGP) || !mutt_is_multipart_encrypted(m))
	)
    {
      idx = mutt_gen_attach_list (m->parts, m->type, idx, idxlen, idxmax, level, compose);
    }
    else
    {
      if (!idx[*idxlen])
	idx[*idxlen] = (ATTACHPTR *) safe_calloc (1, sizeof (ATTACHPTR));

      new = idx[(*idxlen)++];
      new->content = m;
      m->aptr = new;
      new->parent_type = parent_type;
      new->level = level;

      /* We don't support multipart messages in the compose menu yet */
      if (!compose && !m->collapsed && 
	  ((m->type == TYPEMULTIPART
            && (!(WithCrypto & APPLICATION_PGP)
                || !mutt_is_multipart_encrypted (m))
	    )
	   || mutt_is_message_type(m->type, m->subtype)))
      {
	idx = mutt_gen_attach_list (m->parts, m->type, idx, idxlen, idxmax, level + 1, compose);
      }
    }
  }

  if (level == 0)
    mutt_update_tree (idx, *idxlen);

  return (idx);
}
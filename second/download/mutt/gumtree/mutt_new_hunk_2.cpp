    mutt_free_alias (&new);
    return;
  }
  new->addr->personal = safe_strdup (buf);

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), new->addr, 1);
  snprintf (prompt, sizeof (prompt), _("[%s = %s] Accept?"), new->name, buf);
  if (mutt_yesorno (prompt, M_YES) != M_YES)
  {
    mutt_free_alias (&new);
    return;
  }

  mutt_alias_add_reverse (new);
  
  if ((t = Aliases))
  {
    while (t->next)
      t = t->next;
    t->next = new;
  }

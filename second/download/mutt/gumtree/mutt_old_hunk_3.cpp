    Aliases = new;

  strfcpy (buf, NONULL (AliasFile), sizeof (buf));
  if (mutt_get_field (_("Save to file: "), buf, sizeof (buf), M_FILE) != 0)
    return;
  mutt_expand_path (buf, sizeof (buf));
  if ((rc = fopen (buf, "a")))
  {
    buf[0] = 0;
    rfc822_write_address (buf, sizeof (buf), new->addr);
    fprintf (rc, "alias %s ", new->name);
    write_safe_address (rc, buf);
    fputc ('\n', rc);
    fclose (rc);
    mutt_message _("Alias added.");
  }
  else
    mutt_perror (buf);
}

/*
 * This routine looks to see if the user has an alias defined for the given
 * address.
 */
ADDRESS *alias_reverse_lookup (ADDRESS *a)
{
  ALIAS *t = Aliases;
  ADDRESS *ap;

  if (!a || !a->mailbox)
    return NULL;

  for (; t; t = t->next)
  {
    /* cycle through all addresses if this is a group alias */
    for (ap = t->addr; ap; ap = ap->next)
    {
      if (!ap->group && ap->mailbox &&
	  ascii_strcasecmp (ap->mailbox, a->mailbox) == 0)
	return ap;
    }
  }
  return 0;
}

/* alias_complete() -- alias completion routine
 *
 * given a partial alias, this routine attempts to fill in the alias
 * from the alias list as much as possible. if given empty search string

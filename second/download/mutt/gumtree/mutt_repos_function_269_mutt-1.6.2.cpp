int mutt_parse_hook (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  HOOK *ptr;
  BUFFER command, pattern;
  int rc, not = 0;
  regex_t *rx = NULL;
  pattern_t *pat = NULL;
  char path[_POSIX_PATH_MAX];

  mutt_buffer_init (&pattern);
  mutt_buffer_init (&command);

  if (*s->dptr == '!')
  {
    s->dptr++;
    SKIPWS (s->dptr);
    not = 1;
  }

  mutt_extract_token (&pattern, s, 0);

  if (!MoreArgs (s))
  {
    strfcpy (err->data, _("too few arguments"), err->dsize);
    goto error;
  }

  mutt_extract_token (&command, s, (data & (M_FOLDERHOOK | M_SENDHOOK | M_SEND2HOOK | M_ACCOUNTHOOK | M_REPLYHOOK)) ?  M_TOKEN_SPACE : 0);

  if (!command.data)
  {
    strfcpy (err->data, _("too few arguments"), err->dsize);
    goto error;
  }

  if (MoreArgs (s))
  {
    strfcpy (err->data, _("too many arguments"), err->dsize);
    goto error;
  }

  if (data & (M_FOLDERHOOK | M_MBOXHOOK))
  {
    /* Accidentally using the ^ mailbox shortcut in the .muttrc is a
     * common mistake */
    if ((*pattern.data == '^') && (! CurrentFolder))
    {
      strfcpy (err->data, _("current mailbox shortcut '^' is unset"), err->dsize);
      goto error;
    }

    strfcpy (path, pattern.data, sizeof (path));
    _mutt_expand_path (path, sizeof (path), 1);

    /* Check for other mailbox shortcuts that expand to the empty string.
     * This is likely a mistake too */
    if (!*path && *pattern.data)
    {
      strfcpy (err->data, _("mailbox shortcut expanded to empty regexp"), err->dsize);
      goto error;
    }

    FREE (&pattern.data);
    memset (&pattern, 0, sizeof (pattern));
    pattern.data = safe_strdup (path);
  }
  else if (DefaultHook && !(data & (M_CHARSETHOOK | M_ICONVHOOK | M_ACCOUNTHOOK))
           && (!WithCrypto || !(data & M_CRYPTHOOK))
      )
  {
    char tmp[HUGE_STRING];

    /* At this stage remain only message-hooks, reply-hooks, send-hooks,
     * send2-hooks, save-hooks, and fcc-hooks: All those allowing full
     * patterns. If given a simple regexp, we expand $default_hook.
     */
    strfcpy (tmp, pattern.data, sizeof (tmp));
    mutt_check_simple (tmp, sizeof (tmp), DefaultHook);
    FREE (&pattern.data);
    memset (&pattern, 0, sizeof (pattern));
    pattern.data = safe_strdup (tmp);
  }

  if (data & (M_MBOXHOOK | M_SAVEHOOK | M_FCCHOOK))
  {
    strfcpy (path, command.data, sizeof (path));
    mutt_expand_path (path, sizeof (path));
    FREE (&command.data);
    memset (&command, 0, sizeof (command));
    command.data = safe_strdup (path);
  }

  /* check to make sure that a matching hook doesn't already exist */
  for (ptr = Hooks; ptr; ptr = ptr->next)
  {
    if (ptr->type == data &&
	ptr->rx.not == not &&
	!mutt_strcmp (pattern.data, ptr->rx.pattern))
    {
      if (data & (M_FOLDERHOOK | M_SENDHOOK | M_SEND2HOOK | M_MESSAGEHOOK | M_ACCOUNTHOOK | M_REPLYHOOK | M_CRYPTHOOK))
      {
	/* these hooks allow multiple commands with the same
	 * pattern, so if we've already seen this pattern/command pair, just
	 * ignore it instead of creating a duplicate */
	if (!mutt_strcmp (ptr->command, command.data))
	{
	  FREE (&command.data);
	  FREE (&pattern.data);
	  return 0;
	}
      }
      else
      {
	/* other hooks only allow one command per pattern, so update the
	 * entry with the new command.  this currently does not change the
	 * order of execution of the hooks, which i think is desirable since
	 * a common action to perform is to change the default (.) entry
	 * based upon some other information. */
	FREE (&ptr->command);
	ptr->command = command.data;
	FREE (&pattern.data);
	return 0;
      }
    }
    if (!ptr->next)
      break;
  }

  if (data & (M_SENDHOOK | M_SEND2HOOK | M_SAVEHOOK | M_FCCHOOK | M_MESSAGEHOOK | M_REPLYHOOK))
  {
    if ((pat = mutt_pattern_comp (pattern.data,
	   (data & (M_SENDHOOK | M_SEND2HOOK | M_FCCHOOK)) ? 0 : M_FULL_MSG,
				  err)) == NULL)
      goto error;
  }
  else
  {
    /* Hooks not allowing full patterns: Check syntax of regexp */
    rx = safe_malloc (sizeof (regex_t));
#ifdef M_CRYPTHOOK
    if ((rc = REGCOMP (rx, NONULL(pattern.data), ((data & (M_CRYPTHOOK|M_CHARSETHOOK|M_ICONVHOOK)) ? REG_ICASE : 0))) != 0)
#else
    if ((rc = REGCOMP (rx, NONULL(pattern.data), (data & (M_CHARSETHOOK|M_ICONVHOOK)) ? REG_ICASE : 0)) != 0)
#endif /* M_CRYPTHOOK */
    {
      regerror (rc, rx, err->data, err->dsize);
      FREE (&rx);
      goto error;
    }
  }

  if (ptr)
  {
    ptr->next = safe_calloc (1, sizeof (HOOK));
    ptr = ptr->next;
  }
  else
    Hooks = ptr = safe_calloc (1, sizeof (HOOK));
  ptr->type = data;
  ptr->command = command.data;
  ptr->pattern = pat;
  ptr->rx.pattern = pattern.data;
  ptr->rx.rx = rx;
  ptr->rx.not = not;
  return 0;

error:
  FREE (&pattern.data);
  FREE (&command.data);
  return (-1);
}
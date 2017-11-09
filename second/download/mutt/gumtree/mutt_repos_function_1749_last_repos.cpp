static int add_to_replace_list (REPLACE_LIST **list, const char *pat, const char *templ, BUFFER *err)
{
  REPLACE_LIST *t = NULL, *last = NULL;
  REGEXP *rx;
  int n;
  const char *p;

  if (!pat || !*pat || !templ)
    return 0;

  if (!(rx = mutt_compile_regexp (pat, REG_ICASE)))
  {
    snprintf (err->data, err->dsize, _("Bad regexp: %s"), pat);
    return -1;
  }

  /* check to make sure the item is not already on this list */
  for (last = *list; last; last = last->next)
  {
    if (ascii_strcasecmp (rx->pattern, last->rx->pattern) == 0)
    {
      /* Already on the list. Formerly we just skipped this case, but
       * now we're supporting removals, which means we're supporting
       * re-adds conceptually. So we probably want this to imply a
       * removal, then do an add. We can achieve the removal by freeing
       * the template, and leaving t pointed at the current item.
       */
      t = last;
      FREE(&t->template);
      break;
    }
    if (!last->next)
      break;
  }

  /* If t is set, it's pointing into an extant REPLACE_LIST* that we want to
   * update. Otherwise we want to make a new one to link at the list's end.
   */
  if (!t)
  {
    t = mutt_new_replace_list();
    t->rx = rx;
    if (last)
      last->next = t;
    else
      *list = t;
  }

  /* Now t is the REPLACE_LIST* that we want to modify. It is prepared. */
  t->template = safe_strdup(templ);

  /* Find highest match number in template string */
  t->nmatch = 0;
  for (p = templ; *p;)
  {
    if (*p == '%')
    {
        n = atoi(++p);
        if (n > t->nmatch)
          t->nmatch = n;
        while (*p && isdigit((int)*p))
          ++p;
    }
    else
        ++p;
  }

  if (t->nmatch > t->rx->rx->re_nsub)
  {
    snprintf (err->data, err->dsize, "%s", _("Not enough subexpressions for "
                                       "template"));
    remove_from_replace_list(list, pat);
    return -1;
  }

  t->nmatch++;         /* match 0 is always the whole expr */

  return 0;
}
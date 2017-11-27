static int tr_action_invoke (tr_action_t *act_head, /* {{{ */
    char *buffer_in, size_t buffer_in_size, int may_be_empty)
{
  tr_action_t *act;
  int status;
  char buffer[DATA_MAX_NAME_LEN];
  regmatch_t matches[8];

  if (act_head == NULL)
    return (-EINVAL);

  sstrncpy (buffer, buffer_in, sizeof (buffer));
  memset (matches, 0, sizeof (matches));

  DEBUG ("target_replace plugin: tr_action_invoke: <- buffer = %s;", buffer);

  for (act = act_head; act != NULL; act = act->next)
  {
    char temp[DATA_MAX_NAME_LEN];
    char *subst_status;

    status = regexec (&act->re, buffer,
        STATIC_ARRAY_SIZE (matches), matches,
        /* flags = */ 0);
    if (status == REG_NOMATCH)
      continue;
    else if (status != 0)
    {
      char errbuf[1024] = "";

      regerror (status, &act->re, errbuf, sizeof (errbuf));
      ERROR ("Target `replace': Executing a regular expression failed: %s.",
          errbuf);
      continue;
    }

    subst_status = subst (temp, sizeof (temp), buffer,
        matches[0].rm_so, matches[0].rm_eo, act->replacement);
    if (subst_status == NULL)
    {
      ERROR ("Target `replace': subst (buffer = %s, start = %zu, end = %zu, "
          "replacement = %s) failed.",
          buffer, (size_t) matches[0].rm_so, (size_t) matches[0].rm_eo,
          act->replacement);
      continue;
    }
    sstrncpy (buffer, temp, sizeof (buffer));

    DEBUG ("target_replace plugin: tr_action_invoke: -- buffer = %s;", buffer);
  } /* for (act = act_head; act != NULL; act = act->next) */

  if ((may_be_empty == 0) && (buffer[0] == 0))
  {
    WARNING ("Target `replace': Replacement resulted in an empty string, "
        "which is not allowed for this buffer (`host' or `plugin').");
    return (0);
  }

  DEBUG ("target_replace plugin: tr_action_invoke: -> buffer = %s;", buffer);
  sstrncpy (buffer_in, buffer, buffer_in_size);

  return (0);
}
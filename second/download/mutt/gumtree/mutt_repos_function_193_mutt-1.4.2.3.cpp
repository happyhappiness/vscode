static char *_mutt_string_hook (const char *match, int hook)
{
  HOOK *tmp = Hooks;

  for (; tmp; tmp = tmp->next)
  {
    if ((tmp->type & hook) && ((match &&
	 regexec (tmp->rx.rx, match, 0, NULL, 0) == 0) ^ tmp->rx.not))
      return (tmp->command);
  }
  return (NULL);
}
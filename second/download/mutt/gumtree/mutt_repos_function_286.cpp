static LIST *_mutt_list_hook (const char *match, int hook)
{
  HOOK *tmp = Hooks;
  LIST *matches = NULL;

  for (; tmp; tmp = tmp->next)
  {
    if ((tmp->type & hook) &&
        ((match && regexec (tmp->rx.rx, match, 0, NULL, 0) == 0) ^ tmp->rx.not))
      matches = mutt_add_list (matches, tmp->command);
  }
  return (matches);
}
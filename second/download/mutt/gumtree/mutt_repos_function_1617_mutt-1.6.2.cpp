static int mutt_option_index (char *s)
{
  int i;

  for (i = 0; MuttVars[i].option; i++)
    if (mutt_strcmp (s, MuttVars[i].option) == 0)
      return (MuttVars[i].type == DT_SYN ?  mutt_option_index ((char *) MuttVars[i].data) : i);
  return (-1);
}
static int mix_chain_add (MIXCHAIN *chain, const char *s, 
			  REMAILER **type2_list)
{
  int i;
  
  if (chain->cl >= MAXMIXES)
    return -1;
  
  if (!mutt_strcmp (s, "0") || !ascii_strcasecmp (s, "<random>"))
  {
    chain->ch[chain->cl++] = 0;
    return 0;
  }

  for (i = 0; type2_list[i]; i++)
  {
    if (!ascii_strcasecmp (s, type2_list[i]->shortname))
    {
      chain->ch[chain->cl++] = i;
      return 0;
    }
  }
  
  /* replace unknown remailers by <random> */
  
  if (!type2_list[i])
    chain->ch[chain->cl++] = 0;

  return 0;
}
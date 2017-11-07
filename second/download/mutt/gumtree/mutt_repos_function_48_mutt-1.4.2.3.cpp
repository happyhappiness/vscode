static ADDRESS *set_reverse_name (ENVELOPE *env)
{
  ADDRESS *tmp;

  for (tmp = env->to; tmp; tmp = tmp->next)
  {
    if (mutt_addr_is_user (tmp))
      break;
  }
  if (!tmp)
  {
    for (tmp = env->cc; tmp; tmp = tmp->next)
    {
      if (mutt_addr_is_user (tmp))
	break;
    }
  }
  if (!tmp && mutt_addr_is_user (env->from))
    tmp = env->from;
  if (tmp)
  {
    tmp = rfc822_cpy_adr_real (tmp);
    if (!option (OPTREVREAL))
      FREE (&tmp->personal);
    if (!tmp->personal)
      tmp->personal = safe_strdup (Realname);
  }
  return (tmp);
}
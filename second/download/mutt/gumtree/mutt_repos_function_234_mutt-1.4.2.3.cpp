int pgp_get_keys (HEADER *msg, char **pgpkeylist)
{
  /* Do a quick check to make sure that we can find all of the encryption
   * keys if the user has requested this service.
   */

  set_option (OPTPGPCHECKTRUST);

  *pgpkeylist = NULL;
  if (msg->pgp & PGPENCRYPT)
  {
    if ((*pgpkeylist = pgp_findKeys (msg->env->to, msg->env->cc,
				      msg->env->bcc)) == NULL)
      return (-1);
  }

  return (0);
}
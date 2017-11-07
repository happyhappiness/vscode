void mutt_select_fcc (char *path, size_t pathlen, HEADER *hdr)
{
  ADDRESS *adr;
  char buf[_POSIX_PATH_MAX];
  ENVELOPE *env = hdr->env;

  if (mutt_addr_hook (path, pathlen, M_FCCHOOK, NULL, hdr) != 0)
  {
    if ((option (OPTSAVENAME) || option (OPTFORCENAME)) &&
	(env->to || env->cc || env->bcc))
    {
      adr = env->to ? env->to : (env->cc ? env->cc : env->bcc);
      mutt_safe_path (buf, sizeof (buf), adr);
      snprintf (path, pathlen, "%s/%s", NONULL (Maildir), buf);
      if (!option (OPTFORCENAME) && mx_access (path, W_OK) != 0)
	strfcpy (path, NONULL (Outbox), pathlen);
    }
    else
      strfcpy (path, NONULL (Outbox), pathlen);
  }
  mutt_pretty_mailbox (path);
}
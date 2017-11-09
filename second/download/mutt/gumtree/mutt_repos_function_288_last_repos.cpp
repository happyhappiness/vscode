void mutt_default_save (char *path, size_t pathlen, HEADER *hdr)
{
  *path = 0;
  if (mutt_addr_hook (path, pathlen, MUTT_SAVEHOOK, Context, hdr) != 0)
  {
    char tmp[_POSIX_PATH_MAX];
    ADDRESS *adr;
    ENVELOPE *env = hdr->env;
    int fromMe = mutt_addr_is_user (env->from);

    if (!fromMe && env->reply_to && env->reply_to->mailbox)
      adr = env->reply_to;
    else if (!fromMe && env->from && env->from->mailbox)
      adr = env->from;
    else if (env->to && env->to->mailbox)
      adr = env->to;
    else if (env->cc && env->cc->mailbox)
      adr = env->cc;
    else
      adr = NULL;
    if (adr)
    {
      mutt_safe_path (tmp, sizeof (tmp), adr);
      snprintf (path, pathlen, "=%s", tmp);
    }
  }
}
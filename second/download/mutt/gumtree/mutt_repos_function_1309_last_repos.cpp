static char **
add_args (char **args, size_t *argslen, size_t *argsmax, ADDRESS *addr)
{
  for (; addr; addr = addr->next)
  {
    /* weed out group mailboxes, since those are for display only */
    if (addr->mailbox && !addr->group)
    {
      if (*argslen == *argsmax)
	safe_realloc (&args, (*argsmax += 5) * sizeof (char *));
      args[(*argslen)++] = addr->mailbox;
    }
  }
  return (args);
}
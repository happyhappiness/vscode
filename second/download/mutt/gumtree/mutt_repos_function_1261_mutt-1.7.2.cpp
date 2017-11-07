static char **
add_option (char **args, size_t *argslen, size_t *argsmax, char *s)
{
  if (*argslen == *argsmax)
    safe_realloc (&args, (*argsmax += 5) * sizeof (char *));
  args[(*argslen)++] = s;
  return (args);
}
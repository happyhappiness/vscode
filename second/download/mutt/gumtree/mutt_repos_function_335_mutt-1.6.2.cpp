static int get_op (const struct binding_t *bindings, const char *start, size_t len)
{
  int i;

  for (i = 0; bindings[i].name; i++)
  {
    if (!ascii_strncasecmp (start, bindings[i].name, len) &&   
	mutt_strlen (bindings[i].name) == len)
      return bindings[i].op;
  }

  return OP_NULL;
}
static char *get_func (const struct binding_t *bindings, int op)
{
  int i;

  for (i = 0; bindings[i].name; i++)
  {
    if (bindings[i].op == op)
      return bindings[i].name;
  }

  return NULL;
}
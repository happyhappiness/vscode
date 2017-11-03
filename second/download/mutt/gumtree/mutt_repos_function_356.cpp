static int
try_bind (char *key, int menu, char *func, const struct binding_t *bindings)
{
  int i;
  
  for (i = 0; bindings[i].name; i++)
    if (mutt_strcmp (func, bindings[i].name) == 0)
    {
      km_bindkey (key, menu, bindings[i].op);
      return (0);
    }
  return (-1);
}
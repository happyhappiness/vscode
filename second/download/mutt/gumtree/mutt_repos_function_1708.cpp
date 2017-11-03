static const char* myvar_get (const char* var)
{
  myvar_t* cur;

  for (cur = MyVars; cur; cur = cur->next)
    if (!mutt_strcmp (cur->name, var))
      return NONULL(cur->value);

  return NULL;
}
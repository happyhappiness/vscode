static void myvar_set (const char* var, const char* val)
{
  myvar_t** cur;

  for (cur = &MyVars; *cur; cur = &((*cur)->next))
    if (!mutt_strcmp ((*cur)->name, var))
      break;

  if (!*cur)
    *cur = safe_calloc (1, sizeof (myvar_t));
  
  if (!(*cur)->name)
    (*cur)->name = safe_strdup (var);
  
  mutt_str_replace (&(*cur)->value, val);
}
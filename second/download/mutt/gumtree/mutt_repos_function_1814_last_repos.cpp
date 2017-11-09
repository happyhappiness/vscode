static void myvar_del (const char* var)
{
  myvar_t **cur;
  myvar_t *tmp;
  

  for (cur = &MyVars; *cur; cur = &((*cur)->next))
    if (!mutt_strcmp ((*cur)->name, var))
      break;
  
  if (*cur) 
  {
    tmp = (*cur)->next;
    FREE (&(*cur)->name);
    FREE (&(*cur)->value);
    FREE (cur);		/* __FREE_CHECKED__ */
    *cur = tmp;
  }
}
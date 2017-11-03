int safe_fclose (FILE **f)
{
  int r = 0;
  
  if (*f)
    r = fclose (*f);
      
  *f = NULL;
  return r;
}
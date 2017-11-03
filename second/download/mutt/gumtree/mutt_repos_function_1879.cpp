static int commit_buff (char *buff, char **d, FILE *out, int docstat)
{
  if (*d > buff)
  {
    **d = '\0';
    docstat = print_it (SP_STR, buff, out, docstat);
    *d = buff;
  }

  return docstat;
}
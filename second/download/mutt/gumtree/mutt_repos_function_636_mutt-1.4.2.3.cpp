static char *flowed_skip_indent (char *prefix, char *cont)
{
  for (; *cont == ' ' || *cont == '\t'; cont++)
    *prefix++ = *cont;
  *prefix = '\0';
  return cont;
}
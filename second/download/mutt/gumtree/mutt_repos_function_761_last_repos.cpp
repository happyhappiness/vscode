static void
print_dn_parts (FILE *fp, struct dn_array_s *dn)
{
  static const char * const stdpart[] = {
    "CN", "OU", "O", "STREET", "L", "ST", "C", NULL 
  };
  int any=0, any2=0, i;
  
  for (i=0; stdpart[i]; i++)
    {
      if (any)
        fputs (", ", fp);
      any = print_dn_part (fp, dn, stdpart[i]);
    }
  /* now print the rest without any specific ordering */
  for (; dn->key; dn++)
    {
      for (i=0; stdpart[i]; i++)
        {
          if (!strcmp (dn->key, stdpart[i]))
            break;
        }
      if (!stdpart[i])
        {
          if (any)
            fputs (", ", fp);
          if (!any2)
            fputs ("(", fp);
          any = print_dn_part (fp, dn, dn->key);
          any2 = 1;
        }
    }
  if (any2)
    fputs (")", fp);
}
static int
print_dn_part (FILE *fp, struct dn_array_s *dn, const char *key)
{
  int any = 0;

  for (; dn->key; dn++)
    {
      if (!strcmp (dn->key, key))
        {
          if (any)
            fputs (" + ", fp);
          print_utf8 (fp, dn->value, strlen (dn->value));
          any = 1;
        }
    }
  return any;
}
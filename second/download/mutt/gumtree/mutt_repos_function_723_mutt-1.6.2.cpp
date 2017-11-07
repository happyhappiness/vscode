static void
parse_and_print_user_id (FILE *fp, const char *userid)
{
  const char *s;
  int i;

  if (*userid == '<')
    {
      s = strchr (userid+1, '>');
      if (s)
        print_utf8 (fp, userid+1, s-userid-1);
    }
  else if (*userid == '(')
    fputs (_("[Can't display this user ID (unknown encoding)]"), fp);
  else if (!digit_or_letter ((const unsigned char *)userid))
    fputs (_("[Can't display this user ID (invalid encoding)]"), fp);
  else
    {
      struct dn_array_s *dn = parse_dn ((const unsigned char *)userid);
      if (!dn)
        fputs (_("[Can't display this user ID (invalid DN)]"), fp);
      else 
        {
          print_dn_parts (fp, dn);          
          for (i=0; dn[i].key; i++)
            {
              FREE (&dn[i].key);
              FREE (&dn[i].value);
            }
          FREE (&dn);
        }
    }
}
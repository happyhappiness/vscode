static void transform_to_7bit (BODY *a, FILE *fpin)
{
  char buff[_POSIX_PATH_MAX];
  STATE s;
  struct stat sb;

  memset (&s, 0, sizeof (s));
  for (; a; a = a->next)
  {
    if (a->type == TYPEMULTIPART)
    {
      if (a->encoding != ENC7BIT)
	a->encoding = ENC7BIT;

      transform_to_7bit (a->parts, fpin);
    }
    else if (mutt_is_message_type(a->type, a->subtype))
    {
      mutt_message_to_7bit (a, fpin);
    }
    else
    {
      a->noconv = 1;
      a->force_charset = 1;

      mutt_mktemp (buff, sizeof (buff));
      if ((s.fpout = safe_fopen (buff, "w")) == NULL)
      {
	mutt_perror ("fopen");
	return;
      }
      s.fpin = fpin;
      mutt_decode_attachment (a, &s);
      safe_fclose (&s.fpout);
      FREE (&a->d_filename);
      a->d_filename = a->filename;
      a->filename = safe_strdup (buff);
      a->unlink = 1;
      if (stat (a->filename, &sb) == -1)
      {
	mutt_perror ("stat");
	return;
      }
      a->length = sb.st_size;

      mutt_update_encoding (a);
      if (a->encoding == ENC8BIT)
	a->encoding = ENCQUOTEDPRINTABLE;
      else if(a->encoding == ENCBINARY)
	a->encoding = ENCBASE64;
    }
  }
}
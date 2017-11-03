static void pgpring_find_candidates (char *ringfile, const char *hints[], int nhints)
{
  FILE *rfp;
#ifdef HAVE_FGETPOS
  fpos_t pos, keypos;
#else
  LOFF_T pos, keypos;
#endif

  unsigned char *buff = NULL;
  unsigned char pt = 0;
  size_t l = 0;

  short err = 0;
  
  if ((rfp = fopen (ringfile, "r")) == NULL)
  {
    char *error_buf;
    size_t error_buf_len;

    error_buf_len = sizeof ("fopen: ") - 1 + strlen (ringfile) + 1;
    error_buf = safe_malloc (error_buf_len);
    snprintf (error_buf, error_buf_len, "fopen: %s", ringfile);
    perror (error_buf);
    FREE (&error_buf);
    return;
  }

  FGETPOS(rfp,pos);
  FGETPOS(rfp,keypos);

  while (!err && (buff = pgp_read_packet (rfp, &l)) != NULL)
  {
    pt = buff[0] & 0x3f;
    
    if (l < 1)
      continue;
    
    if ((pt == PT_SECKEY) || (pt == PT_PUBKEY))
    {
      keypos = pos;
    }
    else if (pt == PT_NAME)
    {
      char *tmp = safe_malloc (l);

      memcpy (tmp, buff + 1, l - 1);
      tmp[l - 1] = '\0';

      /* mutt_decode_utf8_string (tmp, chs); */

      if (pgpring_string_matches_hint (tmp, hints, nhints))
      {
	pgp_key_t p;

	FSETPOS(rfp, keypos);

	/* Not bailing out here would lead us into an endless loop. */

	if ((p = pgp_parse_keyblock (rfp)) == NULL)
	  err = 1;
	
	pgpring_dump_keyblock (p);
	pgp_free_key (&p);
      }

      FREE (&tmp);
    }

    FGETPOS(rfp,pos);
  }

  safe_fclose (&rfp);

}
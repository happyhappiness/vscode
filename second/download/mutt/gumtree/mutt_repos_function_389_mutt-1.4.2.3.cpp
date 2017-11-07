static short pgp_find_hash (const char *fname)
{
  FILE *in = NULL;
  FILE *out = NULL;
  
  char tempfile[_POSIX_PATH_MAX];
  
  unsigned char *p;
  size_t l;
  
  short rv = -1;
  
  mutt_mktemp (tempfile);
  if ((out = safe_fopen (tempfile, "w+")) == NULL)
  {
    mutt_perror (tempfile);
    goto bye;
  }
  unlink (tempfile);
  
  if ((in = fopen (fname, "r")) == NULL)
  {
    mutt_perror (fname);
    goto bye;
  }
  
  pgp_dearmor (in, out);
  rewind (out);

  if ((p = pgp_read_packet (out, &l)) != NULL)
  {
    rv = pgp_mic_from_packet (p, l);
  }
  else
  {
    dprint (1, (debugfile, "pgp_find_hash: No packet.\n"));
  }
  
  bye:
  
  safe_fclose (&in);
  safe_fclose (&out);
  pgp_release_packet ();
  return rv;
}
static long pgp_copy_clearsigned (STATE *s, long bytes)
{
  long last_pos, offset;
  char buf[HUGE_STRING];
  short complete, armor_header, have_sig;

  last_pos = ftell (s->fpin);
  
  for (complete = 1, armor_header = 1, have_sig = 0;
       bytes > 0 && fgets (buf, sizeof (buf), s->fpin) != NULL;  
       complete = strchr (buf, '\n') != NULL)
  {
    offset   = ftell (s->fpin);
    bytes   -= (offset - last_pos);
    last_pos = offset;
    
    if (!complete)
    {
      if (!armor_header)
	state_puts (buf, s);
      continue;
    }

    if (mutt_strcmp (buf, "-----BEGIN PGP SIGNATURE-----\n") == 0)
    {
      have_sig = 1;
      break;
    }
    
    if (armor_header)
    {
      if (buf[0] == '\n') 
	armor_header = 0;
      continue;
    }
    
    if (s->prefix) 
      state_puts (s->prefix, s);
    
    if (buf[0] == '-' && buf[1] == ' ')
      state_puts (buf + 2, s);
    else
      state_puts (buf, s);
  }
  
  if (!have_sig)
    return bytes;
    
  for (complete = 1;
       bytes > 0 && fgets (buf, sizeof (buf), s->fpin) != NULL;
       complete = strchr (buf, '\n') != NULL)
  {
    offset   = ftell (s->fpin);
    bytes   -= (offset - last_pos);
    last_pos = offset;
    
    if (mutt_strcmp (buf, "-----END PGP SIGNATURE-----\n") == 0)
      break;
  }
  
  return bytes;
}
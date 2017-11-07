pgp_key_t pgp_get_candidates (pgp_ring_t keyring, LIST * hints)
{
  FILE *fp;
  pid_t thepid;
  char buf[LONG_STRING];
  pgp_key_t db = NULL, *kend, k = NULL, kk, mainkey = NULL;
  int is_sub;
  int devnull;

  if ((devnull = open ("/dev/null", O_RDWR)) == -1)
    return NULL;

  mutt_str_replace (&_chs, Charset);
  
  thepid = pgp_invoke_list_keys (NULL, &fp, NULL, -1, -1, devnull,
				 keyring, hints);
  if (thepid == -1)
  {
    close (devnull);
    return NULL;
  }

  kend = &db;
  k = NULL;
  while (fgets (buf, sizeof (buf) - 1, fp))
  {
    if (!(kk = parse_pub_line (buf, &is_sub, k)))
      continue;

    /* Only append kk to the list if it's new. */
    if (kk != k)
    {
      if (k)
	kend = &k->next;
      *kend = k = kk;

      if (is_sub)
      {
	pgp_uid_t **l;
	
	k->flags  |= KEYFLAG_SUBKEY;
	k->parent  = mainkey;
	for (l = &k->address; *l; l = &(*l)->next)
	  ;
	*l = pgp_copy_uids (mainkey->address, k);
      }
      else
	mainkey = k;
    }
  }

  if (ferror (fp))
    mutt_perror ("fgets");

  safe_fclose (&fp);
  mutt_wait_filter (thepid);

  close (devnull);
  
  return db;
}
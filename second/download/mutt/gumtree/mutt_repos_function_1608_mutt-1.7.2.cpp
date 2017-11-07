static void pgpring_dump_keyblock (pgp_key_t p)
{
  pgp_uid_t *uid;
  short first;
  struct tm *tp;
  time_t t;
  
  for (; p; p = p->next)
  {
    first = 1;

    if (p->flags & KEYFLAG_SECRET)
    {
      if (p->flags & KEYFLAG_SUBKEY)
	printf ("ssb:");
      else
	printf ("sec:");
    }
    else 
    {
      if (p->flags & KEYFLAG_SUBKEY)
	printf ("sub:");
      else
	printf ("pub:");
    }
    
    if (p->flags & KEYFLAG_REVOKED)
      putchar ('r');
    if (p->flags & KEYFLAG_EXPIRED)
      putchar ('e');
    if (p->flags & KEYFLAG_DISABLED)
      putchar ('d');

    for (uid = p->address; uid; uid = uid->next, first = 0)
    {
      if (!first)
      {
	printf ("uid:%c::::::::", gnupg_trustletter (uid->trust));
	print_userid (uid->addr);
	printf (":\n");
      }
      else
      {
	if (p->flags & KEYFLAG_SECRET)
	  putchar ('u');
	else
	  putchar (gnupg_trustletter (uid->trust));

	t = p->gen_time;
	tp = gmtime (&t);

	printf (":%d:%d:%s:%04d-%02d-%02d::::", p->keylen, p->numalg, p->keyid,
		1900 + tp->tm_year, tp->tm_mon + 1, tp->tm_mday);
	
	print_userid (uid->addr);
	printf ("::");

	if(pgp_canencrypt(p->numalg))
	  putchar ('e');
	if(pgp_cansign(p->numalg))
	  putchar ('s');
	if (p->flags & KEYFLAG_DISABLED)
	  putchar ('D');
	printf (":\n");

	if (dump_fingerprints) 
          print_fingerprint (p);
      }
      
      if (dump_signatures)
      {
	if (first) pgpring_dump_signatures (p->sigs);
	pgpring_dump_signatures (uid->sigs);
      }
    }
  }
}
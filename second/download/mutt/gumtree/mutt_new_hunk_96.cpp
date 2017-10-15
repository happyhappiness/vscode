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

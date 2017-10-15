	tp = gmtime (&t);

	printf (":%d:%d:%s:%04d-%02d-%02d::::", p->keylen, p->numalg, p->keyid,
		1900 + tp->tm_year, tp->tm_mon + 1, tp->tm_mday);
	
	print_userid (uid->addr);
	printf (":\n");
      }
      
      if (dump_signatures)
      {
	if (first) pgpring_dump_signatures (p->sigs);
	pgpring_dump_signatures (uid->sigs);

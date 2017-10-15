#if USE_HCACHE
	"+USE_HCACHE  "
#else
	"-USE_HCACHE  "
#endif

	);

#ifdef ISPELL
  printf ("ISPELL=\"%s\"\n", ISPELL);
#else
  puts ("-ISPELL");

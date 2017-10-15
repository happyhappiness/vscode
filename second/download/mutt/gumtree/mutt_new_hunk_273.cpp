#ifdef USE_SIDEBAR
	"+USE_SIDEBAR  "
#else
	"-USE_SIDEBAR  "
#endif

#ifdef USE_COMPRESSED
	"+USE_COMPRESSED  "
#else
	"-USE_COMPRESSED  "
#endif

	);

#ifdef ISPELL
  printf ("ISPELL=\"%s\"\n", ISPELL);
#else
  puts ("-ISPELL");

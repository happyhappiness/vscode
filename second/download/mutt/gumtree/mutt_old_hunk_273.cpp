#ifdef USE_SIDEBAR
	"+USE_SIDEBAR  "
#else
	"-USE_SIDEBAR  "
#endif

	);

#ifdef ISPELL
  printf ("ISPELL=\"%s\"\n", ISPELL);
#else
  puts ("-ISPELL");

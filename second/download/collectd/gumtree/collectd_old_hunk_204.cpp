  int i;

  /* Required fields: `PUTNOTIF', severity, time, message */
  if (fields_num < 4)
  {
    DEBUG ("cmd putnotif: Wrong number of fields: %i", fields_num);
    fprintf (fh, "-1 Wrong number of fields: Got %i, expected at least 4.\n",
	fields_num);
    fflush (fh);
    return (-1);
  }

  memset (&n, '\0', sizeof (n));

  status = 0;

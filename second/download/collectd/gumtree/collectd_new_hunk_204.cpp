  int i;

  /* Required fields: `PUTNOTIF', severity, time, message */
  if (fields_num < 4)
  {
    DEBUG ("cmd putnotif: Wrong number of fields: %i", fields_num);
    print_to_socket (fh, "-1 Wrong number of fields: Got %i, "
	"expected at least 4.\n",
	fields_num);
    return (-1);
  }

  memset (&n, '\0', sizeof (n));

  status = 0;

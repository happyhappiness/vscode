    {
    n = atoi(argv[1]);
    }
  else if(argc == 3 && strcmp(argv[1], "run") == 0)
    {
    n = atoi(argv[2]);
    }
  /* Check arguments.  */
  if(n >= 1 && n <= 7 && argc == 3)
    {
    /* This is the child process for a requested test number.  */
    switch (n)
      {
      case 1: return test1(argc, argv);

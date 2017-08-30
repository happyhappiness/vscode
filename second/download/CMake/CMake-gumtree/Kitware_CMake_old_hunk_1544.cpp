    {
    n = atoi(argv[1]);
    }
  else if(argc == 3)
    {
    n = atoi(argv[2]);
    }
  /* Check arguments.  */
  if(n < 1 || n > 7 || (argc == 3 && strcmp(argv[1], "run") != 0))
    {
    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
    return 1;
    }
  if(argc == 3)
    {
    switch (n)
      {
      case 1: return test1(argc, argv);

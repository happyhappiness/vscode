    n = atoi(argv[2]);

    }

  /* Check arguments.  */

  if(n < 1 || n > 7 || (argc == 3 && strcmp(argv[1], "run") != 0))

    {

    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);

    return 1;


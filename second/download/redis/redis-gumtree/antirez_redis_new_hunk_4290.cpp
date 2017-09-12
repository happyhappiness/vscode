    for(j = 0; j < argc; j++)
        argvcopy[j] = sdsnew(argv[j]);

    if (argc < 1) usage();

    /* Read the last argument from stdandard input if needed */
    if ((rc = lookupCommand(argv[0])) != NULL) {

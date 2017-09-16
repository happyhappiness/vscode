	exit(0);

    }

    else if (argc != 3)

	usage();



    tn = tmpnam(NULL);

    if (!(tfp = fopen(tn, "w"))) {

	fprintf(stderr, "Could not open temp file.\n");

	exit(1);

    }



    if (!(f = fopen(argv[1], "r"))) {

	fprintf(stderr,

		"Could not open passwd file %s for reading.\n", argv[1]);

	fprintf(stderr, "Use -c option to create new one.\n");

	exit(1);

    }

    strcpy(user, argv[2]);


	 * read options
	 */
	while (1)
	{
		int c;

		c = getopt (argc, argv, "cd:l"
#if COLLECT_PING
				"p:"
#endif /* COLLECT_PING */
				"P:sh");

		if (c == -1)
			break;

		switch (c)
		{
			case 'c':
				operating_mode = MODE_CLIENT;
				break;

			case 'd':
				basedir = optarg;
				break;

			case 'l':
				operating_mode = MODE_LOCAL;
				break;
#if COLLECT_PING
			case 'p':
				if (num_pinghosts < MAX_PINGHOSTS)
					pinghosts[num_pinghosts++] = optarg;
				else
					fprintf (stderr, "Maximum of %i ping hosts reached.\n", MAX_PINGHOSTS);
				break;
#endif /* COLLECT_PING */
			case 'P':
				plugindir = optarg;
				break;

			case 's':
				operating_mode = MODE_SERVER;
				break;

			case 'h':
			default:
				exit_usage (argv[0]);
		}
				
	}

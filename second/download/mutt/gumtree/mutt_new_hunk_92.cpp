	pfx = NULL;

	for(i = 2; i < argc; ) {
		if(!strcmp(argv[i], "--")) {
			i += 2;
			if(i > argc) {
				print_usage(argv[0]);
			}
			pfx = argv[i-1];
		}
		if(pfx)
			*opt++ = pfx;
		*opt++ = argv[i++];

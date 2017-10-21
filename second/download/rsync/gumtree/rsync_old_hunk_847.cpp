		fprintf(stderr, "usage: t_unsafe LINKDEST SRCDIR\n");
		return 1;
	}

	printf("%s\n",
	       unsafe_symlink(argv[1], argv[2]) ? "unsafe" : "safe");
	
	return 0;
}

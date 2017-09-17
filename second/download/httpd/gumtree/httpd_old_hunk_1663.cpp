#if TESTING
		fprintf(stderr, "Would remove directory %s\n", newcachedir);
#else
		rmdir(newcachedir);
#endif
		--nfiles;
	    }
	    continue;
	}
#endif

	i = read(fd, line, 26);

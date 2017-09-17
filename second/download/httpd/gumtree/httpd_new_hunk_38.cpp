#if TESTING
		fprintf(stderr, "Would remove directory %s\n", newcachedir);
#else
		rmdir(newcachedir);
#endif
		--nfiles;
	    } else {
		/* Directory is not empty. Account for its size: */
		add_long61(&curbytes, ROUNDUP2BLOCKS(buf.st_size));
	    }
	    continue;
	}
#endif

	i = read(fd, line, 26);

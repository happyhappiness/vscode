		printf("%12.0f", (double)buf.st_size);
	printf(" %6ld.%-6ld %6ld %s %s%s\n",
	       (long)buf.st_uid, (long)buf.st_gid, (long)buf.st_nlink,
	       datebuf, fname, linkbuf);
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: " PROGRAM " DIR ...\n"
			"Trivial file listing program for portably checking rsync\n");
		return 1;
	}

	for (argv++; *argv; argv++) {
		list_file(*argv);
	}

	return 0;
}

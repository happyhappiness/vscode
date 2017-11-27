	if ((fh = fopen (file, "w")) == NULL)
	{
		syslog (LOG_ERR, "fopen (%s): %s", file, strerror (errno));
		return (1);
	}

	fprintf (fh, "%d\n", getpid());
	fclose(fh);

	return (0);
} /* static int pidfile_create (const char *file) */
#endif /* COLLECT_DAEMON */


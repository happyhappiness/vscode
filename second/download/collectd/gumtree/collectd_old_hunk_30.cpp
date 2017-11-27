	}
	
	return (0);
}
#endif /* HAVE_LIBRRD */

int pidfile_create (void)
{
	FILE *fh;

	if ((fh = fopen (PIDFILE, "w")) == NULL)
	{
		syslog (LOG_ERR, "fopen (pidfile): %s", strerror (errno));
		return (1);
	}

	fprintf (fh, "%d\n", getpid());
	fclose(fh);


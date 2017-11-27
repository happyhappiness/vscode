static cu_mount_t *cu_mount_getfsstat (void)
{
#if HAVE_GETVFSSTAT
#  define STRUCT_STATFS struct statvfs
#  define CMD_STATFS    getvfsstat
#  define FLAGS_STATFS  ST_NOWAIT
/* #endif HAVE_GETVFSSTAT */
#elif HAVE_GETFSSTAT
#  define STRUCT_STATFS struct statfs
#  define CMD_STATFS    getfsstat
#  define FLAGS_STATFS  MNT_NOWAIT
#endif /* HAVE_GETFSSTAT */

	int bufsize;
	STRUCT_STATFS *buf;

	int num;
	int i;

	cu_mount_t *first = NULL;
	cu_mount_t *last  = NULL;
	cu_mount_t *new   = NULL;

	/* Get the number of mounted file systems */
	if ((bufsize = CMD_STATFS (NULL, 0, FLAGS_STATFS)) < 1)
	{
#if COLLECT_DEBUG
		char errbuf[1024];
		DEBUG ("utils_mount: getv?fsstat failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
#endif /* COLLECT_DEBUG */
		return (NULL);
	}

	if ((buf = (STRUCT_STATFS *) malloc (bufsize * sizeof (STRUCT_STATFS)))
			== NULL)
		return (NULL);
	memset (buf, '\0', bufsize * sizeof (STRUCT_STATFS));

	/* The bufsize needs to be passed in bytes. Really. This is not in the
	 * manpage.. -octo */
	if ((num = CMD_STATFS (buf, bufsize * sizeof (STRUCT_STATFS), FLAGS_STATFS)) < 1)
	{
#if COLLECT_DEBUG
		char errbuf[1024];
		DEBUG ("utils_mount: getv?fsstat failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
#endif /* COLLECT_DEBUG */
		free (buf);
		return (NULL);
	}

	for (i = 0; i < num; i++)
	{
		if ((new = malloc (sizeof (cu_mount_t))) == NULL)
			break;
		memset (new, '\0', sizeof (cu_mount_t));
		
		/* Copy values from `struct mnttab' */
		new->dir         = sstrdup (buf[i].f_mntonname);
		new->spec_device = sstrdup (buf[i].f_mntfromname);
		new->type        = sstrdup (buf[i].f_fstypename);
		new->options     = NULL;
		new->device      = get_device_name (new->options);
		new->next = NULL;

		/* Append to list */
		if (first == NULL)
		{
			first = new;
			last  = new;
		}
		else
		{
			last->next = new;
			last       = new;
		}
	}

	free (buf);

	return (first);
}
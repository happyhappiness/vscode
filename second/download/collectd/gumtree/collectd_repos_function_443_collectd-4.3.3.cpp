static int vserver_read (void)
{
	DIR 			*proc;
	struct dirent 	*dent; /* 42 */

	errno = 0;
	if (NULL == (proc = opendir (PROCDIR)))
	{
		char errbuf[1024];
		ERROR ("vserver plugin: fopen (%s): %s", PROCDIR, 
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (NULL != (dent = readdir (proc)))
	{
		int  len;
		char file[BUFSIZE];

		FILE *fh;
		char buffer[BUFSIZE];

		char *cols[4];

		if (dent->d_name[0] == '.')
			continue;

		/* This is not a directory */
		if (dent->d_type != DT_DIR)
			continue;

		/* socket message accounting */
		len = snprintf (file, BUFSIZE, PROCDIR "/%s/cacct", dent->d_name);
		if ((len < 0) || (len >= BUFSIZE))
			continue;

		if (NULL == (fh = fopen (file, "r")))
		{
			char errbuf[1024];
			ERROR ("Cannot open '%s': %s", file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
		}

		while ((fh != NULL) && (NULL != fgets (buffer, BUFSIZE, fh)))
		{
			counter_t rx;
			counter_t tx;
			char *type_instance;

			if (strsplit (buffer, cols, 4) < 4)
				continue;

			if (0 == strcmp (cols[0], "UNIX:"))
				type_instance = "unix";
			else if (0 == strcmp (cols[0], "INET:"))
				type_instance = "inet";
			else if (0 == strcmp (cols[0], "INET6:"))
				type_instance = "inet6";
			else if (0 == strcmp (cols[0], "OTHER:"))
				type_instance = "other";
			else if (0 == strcmp (cols[0], "UNSPEC:"))
				type_instance = "unspec";
			else
				continue;

			rx = __get_sock_bytes (cols[1]);
			tx = __get_sock_bytes (cols[2]);
			/* cols[3] == errors */

			traffic_submit (dent->d_name, type_instance, rx, tx);
		} /* while (fgets) */

		if (fh != NULL)
		{
			fclose (fh);
			fh = NULL;
		}

		/* thread information and load */
		len = snprintf (file, BUFSIZE, PROCDIR "/%s/cvirt", dent->d_name);
		if ((len < 0) || (len >= BUFSIZE))
			continue;

		if (NULL == (fh = fopen (file, "r")))
		{
			char errbuf[1024];
			ERROR ("Cannot open '%s': %s", file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
		}

		while ((fh != NULL) && (NULL != fgets (buffer, BUFSIZE, fh)))
		{
			int n = strsplit (buffer, cols, 4);

			if (2 == n)
			{
				char   *type_instance;
				gauge_t value;

				if (0 == strcmp (cols[0], "nr_threads:"))
					type_instance = "total";
				else if (0 == strcmp (cols[0], "nr_running:"))
					type_instance = "running";
				else if (0 == strcmp (cols[0], "nr_unintr:"))
					type_instance = "uninterruptable";
				else if (0 == strcmp (cols[0], "nr_onhold:"))
					type_instance = "onhold";
				else
					continue;

				value = atof (cols[1]);
				submit_gauge (dent->d_name, "vs_threads", type_instance, value);
			}
			else if (4 == n) {
				if (0 == strcmp (cols[0], "loadavg:"))
				{
					gauge_t snum = atof (cols[1]);
					gauge_t mnum = atof (cols[2]);
					gauge_t lnum = atof (cols[3]);
					load_submit (dent->d_name, snum, mnum, lnum);
				}
			}
		} /* while (fgets) */

		if (fh != NULL)
		{
			fclose (fh);
			fh = NULL;
		}

		/* processes and memory usage */
		len = snprintf (file, BUFSIZE, PROCDIR "/%s/limit", dent->d_name);
		if ((len < 0) || (len >= BUFSIZE))
			continue;

		if (NULL == (fh = fopen (file, "r")))
		{
			char errbuf[1024];
			ERROR ("Cannot open '%s': %s", file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
		}

		while ((fh != NULL) && (NULL != fgets (buffer, BUFSIZE, fh)))
		{
			char *type = "vs_memory";
			char *type_instance;
			gauge_t value;

			if (strsplit (buffer, cols, 2) < 2)
				continue;

			if (0 == strcmp (cols[0], "PROC:"))
			{
				type = "vs_processes";
				type_instance = "";
				value = atof (cols[1]);
			}
			else
			{
				if (0 == strcmp (cols[0], "VM:"))
					type_instance = "vm";
				else if (0 == strcmp (cols[0], "VML:"))
					type_instance = "vml";
				else if (0 == strcmp (cols[0], "RSS:"))
					type_instance = "rss";
				else if (0 == strcmp (cols[0], "ANON:"))
					type_instance = "anon";
				else
					continue;

				value = atof (cols[1]) * pagesize;
			}

			submit_gauge (dent->d_name, type, type_instance, value);
		} /* while (fgets) */

		if (fh != NULL)
		{
			fclose (fh);
			fh = NULL;
		}
	} /* while (readdir) */

	closedir (proc);

	return (0);
}
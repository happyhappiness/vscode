fprintf (stderr, "logfile plugin: fopen (%s) failed: %s\n",
					(log_file == NULL) ? "<null>" : log_file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
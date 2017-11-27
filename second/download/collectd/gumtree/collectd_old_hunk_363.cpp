					(log_file == NULL) ? DEFAULT_LOGFILE : log_file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
	}
	else
	{
		if (print_timestamp)
			fprintf (fh, "[%s] %s\n", timestamp_str, msg);
		else
			fprintf (fh, "%s\n", msg);

		if (do_close != 0)
			fclose (fh);
	}

	pthread_mutex_unlock (&file_lock);

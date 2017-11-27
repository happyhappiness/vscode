static int rrd_write (const data_set_t *ds, const value_list_t *vl)
{
	struct stat  statbuf;
	char         filename[512];
	char         values[512];
	rrd_cache_t *rc;
	time_t       now;

	if (value_list_to_filename (filename, sizeof (filename), ds, vl) != 0)
		return (-1);

	if (value_list_to_string (values, sizeof (values), ds, vl) != 0)
		return (-1);

	if (stat (filename, &statbuf) == -1)
	{
		if (errno == ENOENT)
		{
			if (rrd_create_file (filename, ds))
				return (-1);
		}
		else
		{
			char errbuf[1024];
			ERROR ("stat(%s) failed: %s", filename,
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}
	}
	else if (!S_ISREG (statbuf.st_mode))
	{
		ERROR ("stat(%s): Not a regular file!",
				filename);
		return (-1);
	}

	pthread_mutex_lock (&cache_lock);
	rc = rrd_cache_insert (filename, values, vl->time);
	if (rc == NULL)
	{
		pthread_mutex_unlock (&cache_lock);
		return (-1);
	}

	if (cache == NULL)
	{
		rrd_write_cache_entry (filename, rc);
		/* rc's value-list is free's by `rrd_write_cache_entry' */
		sfree (rc);
		pthread_mutex_unlock (&cache_lock);
		return (0);
	}

	now = time (NULL);

	DEBUG ("age (%s) = %i", filename, now - rc->first_value);

	/* `rc' is not free'd here, because we'll likely reuse it. If not, then
	 * the next flush will remove this entry.  */
	if ((now - rc->first_value) >= cache_timeout)
		rrd_write_cache_entry (filename, rc);

	if ((now - cache_flush_last) >= cache_flush_timeout)
		rrd_cache_flush (cache_flush_timeout);

	pthread_mutex_unlock (&cache_lock);
	return (0);
}
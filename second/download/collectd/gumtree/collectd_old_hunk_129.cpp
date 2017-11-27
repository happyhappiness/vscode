		{
			write_rate = 1.0 / wps;
		}
	}
	else if (strcasecmp ("RandomTimeout", key) == 0)
        {
		int tmp;

		tmp = atoi (value);
		if (tmp < 0)
		{
			fprintf (stderr, "rrdtool: `RandomTimeout' must "
					"be greater than or equal to zero.\n");
			ERROR ("rrdtool: `RandomTimeout' must "
					"be greater then or equal to zero.");
		}
		else
		{
			random_timeout = tmp;
		}
	}
	else
	{
		return (-1);
	}
	return (0);
} /* int rrd_config */

static int rrd_shutdown (void)
{
	pthread_mutex_lock (&cache_lock);
	rrd_cache_flush (-1);
	pthread_mutex_unlock (&cache_lock);

	pthread_mutex_lock (&queue_lock);
	do_shutdown = 1;
	pthread_cond_signal (&queue_cond);
	pthread_mutex_unlock (&queue_lock);

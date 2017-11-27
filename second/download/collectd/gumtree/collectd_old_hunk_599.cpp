			return (1);

		dummy = value_copy;
		while ((ptr = strtok_r (dummy, ", \t", &saveptr)) != NULL)
		{
			dummy = NULL;
			
			tmp_alloc = realloc (rrdcreate_config.timespans,
					sizeof (int) * (rrdcreate_config.timespans_num + 1));
			if (tmp_alloc == NULL)
			{
				fprintf (stderr, "rrdtool: realloc failed.\n");
				ERROR ("rrdtool: realloc failed.\n");

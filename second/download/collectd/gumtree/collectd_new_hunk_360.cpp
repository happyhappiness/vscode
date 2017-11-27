			else if (values[i] == ',')
				values[i] = ':';
		}

		fprintf (use_stdio == 1 ? stdout : stderr,
			 "PUTVAL %s interval=%i %s\n",
			 filename, vl->interval, values);
		return (0);
	}

	if (stat (filename, &statbuf) == -1)
	{
		if (errno == ENOENT)

		if (fields_num < 1)
		{
			fprintf (fhout, "-1 Internal error\n");
			fclose (fhin);
			fclose (fhout);
			pthread_exit ((void *) 1);
			return ((void *) 1);
		}

		if (strcasecmp (fields[0], "getval") == 0)
		{
			handle_getval (fhout, buffer);
		}

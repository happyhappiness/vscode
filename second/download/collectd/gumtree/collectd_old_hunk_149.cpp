			close (fd);
			break;
		}

		if (strcasecmp (fields[0], "getval") == 0)
		{
			us_handle_getval (fh, fields, fields_num);
		}
		else if (strcasecmp (fields[0], "putval") == 0)
		{
			handle_putval (fh, fields, fields_num);
		}
		else if (strcasecmp (fields[0], "listval") == 0)
		{
			us_handle_listval (fh, fields, fields_num);
		}
		else
		{
			fprintf (fh, "-1 Unknown command: %s\n", fields[0]);
			fflush (fh);
		}
	} /* while (fgets) */

	DEBUG ("Exiting..");
	close (fd);

	pthread_exit ((void *) 0);
} /* void *us_handle_client */

static void *us_server_thread (void *arg)
{

static void nfs_read_stats_file (FILE *fh, char *inst)
{
	char buffer[BUFSIZE];

	char plugin_instance[DATA_MAX_NAME_LEN];

	char *fields[48];
	int numfields = 0;

	if (fh == NULL)
		return;

	while (fgets (buffer, BUFSIZE, fh) != NULL)
	{
		numfields = strsplit (buffer, fields, 48);

		if (((numfields - 2) != nfs2_procedures_names_num)
				&& ((numfields - 2)
				       	!= nfs3_procedures_names_num))
			continue;

		if (strcmp (fields[0], "proc2") == 0)
		{
			int i;
			unsigned long long *values;

			if ((numfields - 2) != nfs2_procedures_names_num)
			{
				WARNING ("nfs plugin: Wrong "
						"number of fields (= %i) "
						"for NFSv2 statistics.",
					       	numfields - 2);
				continue;
			}

			snprintf (plugin_instance, sizeof (plugin_instance),
					"v2%s", inst);
			plugin_instance[DATA_MAX_NAME_LEN - 1] = '\0';

			values = (unsigned long long *) malloc (nfs2_procedures_names_num * sizeof (unsigned long long));
			if (values == NULL)
			{
				char errbuf[1024];
				ERROR ("nfs plugin: malloc "
						"failed: %s",
						sstrerror (errno, errbuf, sizeof (errbuf)));
				continue;
			}

			for (i = 0; i < nfs2_procedures_names_num; i++)
				values[i] = atoll (fields[i + 2]);

			nfs_procedures_submit (plugin_instance, values,
					nfs2_procedures_names,
					nfs2_procedures_names_num);

			free (values);
		}
		else if (strncmp (fields[0], "proc3", 5) == 0)
		{
			int i;
			unsigned long long *values;

			if ((numfields - 2) != nfs3_procedures_names_num)
			{
				WARNING ("nfs plugin: Wrong "
						"number of fields (= %i) "
						"for NFSv3 statistics.",
					       	numfields - 2);
				continue;
			}

			snprintf (plugin_instance, sizeof (plugin_instance),
					"v3%s", inst);
			plugin_instance[DATA_MAX_NAME_LEN - 1] = '\0';

			values = (unsigned long long *) malloc (nfs3_procedures_names_num * sizeof (unsigned long long));
			if (values == NULL)
			{
				char errbuf[1024];
				ERROR ("nfs plugin: malloc "
						"failed: %s",
						sstrerror (errno, errbuf, sizeof (errbuf)));
				continue;
			}

			for (i = 0; i < nfs3_procedures_names_num; i++)
				values[i] = atoll (fields[i + 2]);

			nfs_procedures_submit (plugin_instance, values,
					nfs3_procedures_names,
					nfs3_procedures_names_num);

			free (values);
		}
	} /* while (fgets (buffer, BUFSIZE, fh) != NULL) */
}
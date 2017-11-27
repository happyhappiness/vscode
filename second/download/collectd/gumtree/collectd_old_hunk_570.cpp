				filename,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	fprintf (csv, "epoch");
	for (i = 0; i < ds->ds_num; i++)
		fprintf (csv, ",%s", ds->ds[i].name);

	fprintf (csv, "\n");
	fclose (csv);

	return 0;

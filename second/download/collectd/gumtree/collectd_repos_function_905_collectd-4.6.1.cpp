static int csv_create_file (const char *filename, const data_set_t *ds)
{
	FILE *csv;
	int i;

	if (check_create_dir (filename))
		return (-1);

	csv = fopen (filename, "w");
	if (csv == NULL)
	{
		char errbuf[1024];
		ERROR ("csv plugin: fopen (%s) failed: %s",
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
}
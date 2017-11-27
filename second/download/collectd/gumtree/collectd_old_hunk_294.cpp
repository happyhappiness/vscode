
	DEBUG ("csv plugin: csv_write: filename = %s;", filename);

	if (value_list_to_string (values, sizeof (values), ds, vl) != 0)
		return (-1);

	if (stat (filename, &statbuf) == -1)
	{
		if (errno == ENOENT)
		{
			if (csv_create_file (filename, ds))
				return (-1);

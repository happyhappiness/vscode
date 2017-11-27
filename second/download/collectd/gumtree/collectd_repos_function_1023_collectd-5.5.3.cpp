static int multi1_read (char *name, FILE *fh)
{
	char buffer[1024];
	char *fields[10];
	int  fields_num, found_header = 0;
	long long sum_users = 0;

	/* read the file until the "ROUTING TABLE" line is found (no more info after) */
	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		if (strcmp (buffer, "ROUTING TABLE\n") == 0)
			break;

		if (strcmp (buffer, V1STRING) == 0)
		{
			found_header = 1;
			continue;
		}

		/* skip the first lines until the client list section is found */
		if (found_header == 0)
			/* we can't start reading data until this string is found */
			continue;

		fields_num = openvpn_strsplit (buffer,
				fields, STATIC_ARRAY_SIZE (fields));
		if (fields_num < 4)
			continue;

		if (collect_user_count)
			/* If so, sum all users, ignore the individuals*/
		{
			sum_users += 1;
		}
		if (collect_individual_users)
		{
			if (new_naming_schema)
			{
				iostats_submit (name,               /* vpn instance */
						fields[0],          /* "Common Name" */
						atoll (fields[2]),  /* "Bytes Received" */
						atoll (fields[3])); /* "Bytes Sent" */
			}
			else
			{
				iostats_submit (fields[0],          /* "Common Name" */
						NULL,               /* unused when in multimode */
						atoll (fields[2]),  /* "Bytes Received" */
						atoll (fields[3])); /* "Bytes Sent" */
			}
		}
	}

	if (ferror (fh))
		return (0);

	if (collect_user_count)
		numusers_submit(name, name, sum_users);

	return (1);
}
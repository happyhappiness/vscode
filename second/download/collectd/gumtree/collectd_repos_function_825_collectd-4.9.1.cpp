static int openvpn_read (void)
{
	FILE *fh;
	int  i, read;

	read = 0;

	/* call the right read function for every status entry in the list */
	for (i = 0; i < vpn_num; i++)
	{
		fh = fopen (vpn_list[i]->file, "r");
		if (fh == NULL)
		{
			char errbuf[1024];
			WARNING ("openvpn plugin: fopen(%s) failed: %s", vpn_list[i]->file,
				sstrerror (errno, errbuf, sizeof (errbuf)));

			continue;
		}

		switch (vpn_list[i]->version)
		{
			case SINGLE:
				read = single_read(vpn_list[i]->name, fh);
				break;

			case MULTI1:
				read = multi1_read(vpn_list[i]->name, fh);
				break;

			case MULTI2:
				read = multi2_read(vpn_list[i]->name, fh);
				break;

			case MULTI3:
				read = multi3_read(vpn_list[i]->name, fh);
				break;
		}

		fclose (fh);
	}

	return (read ? 0 : -1);
}
static int hddtemp_init (void)
{
#if KERNEL_LINUX
	FILE *fh;
	char buf[1024];
	int buflen;

	char *fields[16];
	int num_fields;

	int major;
	int minor;
	char *name;
	hddname_t *next;
	hddname_t *entry;

	next = first_hddname;
	while (next != NULL)
	{
		entry = next;
		next = entry->next;

		free (entry->name);
		free (entry);
	}
	first_hddname = NULL;

	if ((fh = fopen ("/proc/partitions", "r")) != NULL)
	{
		DEBUG ("Looking at /proc/partitions...");

		while (fgets (buf, sizeof (buf), fh) != NULL)
		{
			/* Delete trailing newlines */
			buflen = strlen (buf);

			while ((buflen > 0) && ((buf[buflen-1] == '\n') || (buf[buflen-1] == '\r')))
				buf[--buflen] = '\0';

			/* We want lines of the form:
			 *
			 *     3     1   77842926 hda1
			 *
			 * ...so, skip everything else. */
			if (buflen == 0)
				continue;
			
			num_fields = strsplit (buf, fields, 16);

			if (num_fields != 4)
				continue;

			major = atoi (fields[0]);
			minor = atoi (fields[1]);

			/* We try to keep only entries, which may correspond to
			 * physical disks and that may have a corresponding
			 * entry in the hddtemp daemon. Basically, this means
			 * IDE and SCSI. */
			switch (major)
			{
				/* SCSI. */
				case SCSI_DISK0_MAJOR:
				case SCSI_DISK1_MAJOR:
				case SCSI_DISK2_MAJOR:
				case SCSI_DISK3_MAJOR:
				case SCSI_DISK4_MAJOR:
				case SCSI_DISK5_MAJOR:
				case SCSI_DISK6_MAJOR:
				case SCSI_DISK7_MAJOR:
#ifdef SCSI_DISK8_MAJOR
				case SCSI_DISK8_MAJOR:
				case SCSI_DISK9_MAJOR:
				case SCSI_DISK10_MAJOR:
				case SCSI_DISK11_MAJOR:
				case SCSI_DISK12_MAJOR:
				case SCSI_DISK13_MAJOR:
				case SCSI_DISK14_MAJOR:
				case SCSI_DISK15_MAJOR:
#endif /* SCSI_DISK8_MAJOR */
					/* SCSI disks minors are multiples of 16.
					 * Keep only those. */
					if (minor % 16)
						continue;
					break;

				/* IDE. */
				case IDE0_MAJOR:
				case IDE1_MAJOR:
				case IDE2_MAJOR:
				case IDE3_MAJOR:
				case IDE4_MAJOR:
				case IDE5_MAJOR:
				case IDE6_MAJOR:
				case IDE7_MAJOR:
				case IDE8_MAJOR:
				case IDE9_MAJOR:
					/* IDE disks minors can only be 0 or 64.
					 * Keep only those. */
					if(minor != 0 && minor != 64)
						continue;
					break;

				/* Skip all other majors. */
				default:
					DEBUG ("Skipping unknown major %i", major);
					continue;
			} /* switch (major) */

			if ((name = strdup (fields[3])) == NULL)
			{
				ERROR ("hddtemp: strdup(%s) == NULL", fields[3]);
				continue;
			}

			if ((entry = (hddname_t *) malloc (sizeof (hddname_t))) == NULL)
			{
				ERROR ("hddtemp: malloc (%u) == NULL",
						(unsigned int) sizeof (hddname_t));
				free (name);
				continue;
			}

			DEBUG ("Found disk: %s (%u:%u).", name, major, minor);

			entry->major = major;
			entry->minor = minor;
			entry->name  = name;
			entry->next  = NULL;

			if (first_hddname == NULL)
			{
				first_hddname = entry;
			}
			else
			{
				entry->next = first_hddname;
				first_hddname = entry;
			}
		}
		fclose (fh);
	}
#if COLLECT_DEBUG
	else
	{
		char errbuf[1024];
		DEBUG ("Could not open /proc/partitions: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}
#endif /* COLLECT_DEBUG */
#endif /* KERNEL_LINUX */

	return (0);
}
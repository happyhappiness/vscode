static int df_read (void)
{
#if HAVE_STATVFS
	struct statvfs statbuf;
#elif HAVE_STATFS
	struct statfs statbuf;
#endif
	/* struct STATANYFS statbuf; */
	cu_mount_t *mnt_list;
	cu_mount_t *mnt_ptr;

	unsigned long long blocksize;
	gauge_t df_free;
	gauge_t df_used;
	char disk_name[256];

	mnt_list = NULL;
	if (cu_mount_getlist (&mnt_list) == NULL)
		return (-1);

	for (mnt_ptr = mnt_list; mnt_ptr != NULL; mnt_ptr = mnt_ptr->next)
	{
		if (ignorelist_match (il_device,
					(mnt_ptr->spec_device != NULL)
					? mnt_ptr->spec_device
					: mnt_ptr->device))
			continue;
		if (ignorelist_match (il_mountpoint, mnt_ptr->dir))
			continue;
		if (ignorelist_match (il_fstype, mnt_ptr->type))
			continue;

		if (STATANYFS (mnt_ptr->dir, &statbuf) < 0)
		{
			char errbuf[1024];
			ERROR ("statv?fs failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			continue;
		}

		if (!statbuf.f_blocks)
			continue;

		blocksize = BLOCKSIZE(statbuf);
		df_free = statbuf.f_bfree * blocksize;
		df_used = (statbuf.f_blocks - statbuf.f_bfree) * blocksize;

		if (by_device) 
		{
			/* eg, /dev/hda1  -- strip off the "/dev/" */
			if (strncmp (mnt_ptr->spec_device, "/dev/", strlen ("/dev/")) == 0)
				sstrncpy (disk_name, mnt_ptr->spec_device + strlen ("/dev/"), sizeof (disk_name));
			else
				sstrncpy (disk_name, mnt_ptr->spec_device, sizeof (disk_name));

			if (strlen(disk_name) < 1) 
			{
				DEBUG("df: no device name name for mountpoint %s, skipping", mnt_ptr->dir);
				continue;
			}
		} 
		else 
		{
			if (strcmp (mnt_ptr->dir, "/") == 0)
			{
				sstrncpy (disk_name, "root", sizeof (disk_name));
			}
			else
			{
				int i, len;

				sstrncpy (disk_name, mnt_ptr->dir + 1, sizeof (disk_name));
				len = strlen (disk_name);

				for (i = 0; i < len; i++)
					if (disk_name[i] == '/')
						disk_name[i] = '-';
			}
		}

		df_submit (disk_name, df_used, df_free);
	}

	cu_mount_freelist (mnt_list);

	return (0);
}
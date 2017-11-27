static int cgroups_read (void)
{
	cu_mount_t *mnt_list;
	cu_mount_t *mnt_ptr;
	_Bool cgroup_found = 0;

	mnt_list = NULL;
	if (cu_mount_getlist (&mnt_list) == NULL)
	{
		ERROR ("cgroups plugin: cu_mount_getlist failed.");
		return (-1);
	}

	for (mnt_ptr = mnt_list; mnt_ptr != NULL; mnt_ptr = mnt_ptr->next)
	{
		/* Find the cgroup mountpoint which contains the cpuacct
		 * controller. */
		if ((strcmp(mnt_ptr->type, "cgroup") != 0)
				|| !cu_mount_checkoption(mnt_ptr->options,
					"cpuacct", /* full = */ 1))
			continue;

		walk_directory (mnt_ptr->dir, read_cpuacct_root,
				/* user_data = */ NULL,
				/* include_hidden = */ 0);
		cgroup_found = 1;
		/* It doesn't make sense to check other cpuacct mount-points
		 * (if any), they contain the same data. */
		break;
	}

	cu_mount_freelist (mnt_list);

	if (!cgroup_found)
	{
		WARNING ("cgroups plugin: Unable to find cgroup "
				"mount-point with the \"cpuacct\" option.");
		return (-1);
	}

	return (0);
}
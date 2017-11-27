static int thermal_sysfs_read (void)
{
	return walk_directory (dirname_sysfs, thermal_sysfs_device_read,
			/* user_data = */ NULL);
}
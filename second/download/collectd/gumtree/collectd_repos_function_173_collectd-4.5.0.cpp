static int thermal_sysfs_device_read (const char *dir, const char *name,
		void *user_data)
{
	char filename[256];
	char data[1024];
	int len;
	int ok = 0;

	if (device_list && ignorelist_match (device_list, name))
		return -1;

	len = snprintf (filename, sizeof (filename), "%s/%s/temp", dirname_sysfs, name);
	if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
		return -1;

	len = read_file_contents (filename, data, sizeof(data));
	if (len > 1 && data[--len] == '\n') {
		char *endptr = NULL;
		double temp;

		data[len] = 0;
		errno = 0;
		temp = strtod (data, &endptr) / 1000.0;

		if (endptr == data + len && errno == 0) {
			thermal_submit(name, TEMP, temp);
			++ok;
		}
	}

	len = snprintf (filename, sizeof (filename), "%s/%s/cur_state", dirname_sysfs, name);
	if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
		return -1;

	len = read_file_contents (filename, data, sizeof(data));
	if (len > 1 && data[--len] == '\n') {
		char *endptr = NULL;
		double state;

		data[len] = 0;
		errno = 0;
		state = strtod (data, &endptr);

		if (endptr == data + len && errno == 0) {
			thermal_submit(name, COOLING_DEV, state);
			++ok;
		}
	}

	return ok ? 0 : -1;
}
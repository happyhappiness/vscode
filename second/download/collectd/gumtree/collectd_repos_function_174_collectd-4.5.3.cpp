static int thermal_procfs_device_read (const char *dir, const char *name,
		void *user_data)
{
	const char str_temp[] = "temperature:";
	char filename[256];
	char data[1024];
	int len;

	if (device_list && ignorelist_match (device_list, name))
		return -1;

	/**
	 * rechot ~ # cat /proc/acpi/thermal_zone/THRM/temperature
	 * temperature:             55 C
	 */
	
	len = snprintf (filename, sizeof (filename), "%s/%s/temperature", dirname_procfs, name);
	if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
		return -1;

	len = read_file_contents (filename, data, sizeof(data));
	if (len > sizeof(str_temp) && data[--len] == '\n' && !strncmp(data, str_temp, sizeof(str_temp)-1)) {
		char *endptr = NULL;
		double temp;
		double celsius, add;
		
		if (data[--len] == 'C') {
			add = 0;
			celsius = 1;
		} else if (data[len] == 'F') {
			add = -32;
			celsius = 5/9;
		} else if (data[len] == 'K') {
			add = -273.15;
			celsius = 1;
		} else
			return -1;

		while (len > 0 && data[--len] == ' ')
			;
		data[len + 1] = 0;

		while (len > 0 && data[--len] != ' ')
			;
		++len;

		errno = 0;
		temp = (strtod (data + len, &endptr) + add) * celsius;

		if (endptr != data + len && errno == 0) {
			thermal_submit(name, TEMP, temp);
			return 0;
		}
	}

	return -1;
}
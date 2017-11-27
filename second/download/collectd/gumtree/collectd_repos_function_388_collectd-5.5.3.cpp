static int battery_read (void) /* {{{ */
{
	int status;

	DEBUG ("battery plugin: Trying sysfs ...");
	status = read_sysfs ();
	if (status == 0)
		return (0);

	DEBUG ("battery plugin: Trying acpi ...");
	status = read_acpi ();
	if (status == 0)
		return (0);

	DEBUG ("battery plugin: Trying pmu ...");
	status = read_pmu ();
	if (status == 0)
		return (0);

	ERROR ("battery plugin: All available input methods failed.");
	return (-1);
}
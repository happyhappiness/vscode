static char *disk_udev_attr_name (struct udev *udev, char *disk_name, const char *attr)
{
	struct udev_device *dev;
	const char *prop;
	char *output = NULL;

	dev = udev_device_new_from_subsystem_sysname (udev, "block", disk_name);
	if (dev != NULL)
	{
		prop = udev_device_get_property_value (dev, attr);
		if (prop) {
			output = strdup (prop);
			DEBUG ("disk plugin: renaming %s => %s", disk_name, output);
		}
		udev_device_unref (dev);
	}
	return output;
}
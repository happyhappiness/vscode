static int
check_devname (const char *dev)
{
	char buf[PATH_MAX];
	char buf2[PATH_MAX];
	int i;

	if (dev[0] == '.')
		return 0;
	
	ssnprintf (buf, sizeof (buf), "/sys/class/net/%s/device/driver", dev);
	buf[sizeof (buf) - 1] = 0;

	memset (buf2, 0, sizeof (buf2));
	i = readlink (buf, buf2, sizeof (buf2) - 1);
	if (i < 0)
		return 0;

	if (strstr (buf2, "/drivers/ath_") == NULL)
		return 0;
	return 1;
}
static int battery_init (void)
{
#if HAVE_IOKIT_IOKITLIB_H || HAVE_IOKIT_PS_IOPOWERSOURCES_H
	/* No init neccessary */
/* #endif HAVE_IOKIT_IOKITLIB_H || HAVE_IOKIT_PS_IOPOWERSOURCES_H */

#elif KERNEL_LINUX
	int len;
	char filename[128];

	for (battery_pmu_num = 0; ; battery_pmu_num++)
	{
		len = ssnprintf (filename, sizeof (filename), battery_pmu_file, battery_pmu_num);

		if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
			break;

		if (access (filename, R_OK))
			break;
	}
#endif /* KERNEL_LINUX */

	return (0);
}
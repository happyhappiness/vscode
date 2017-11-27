static int disk_shutdown (void)
{
#if KERNEL_LINUX
#if HAVE_LIBUDEV
	if (handle_udev != NULL)
		udev_unref(handle_udev);
#endif /* HAVE_LIBUDEV */
#endif /* KERNEL_LINUX */
	return (0);
}
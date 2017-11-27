static int disk_shutdown(void) {
#if KERNEL_LINUX
#if HAVE_UDEV_H
  if (handle_udev != NULL)
    udev_unref(handle_udev);
#endif /* HAVE_UDEV_H */
#endif /* KERNEL_LINUX */
  return 0;
}
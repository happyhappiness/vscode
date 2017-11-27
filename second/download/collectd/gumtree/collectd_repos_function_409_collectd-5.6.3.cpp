static int disk_init(void) {
#if HAVE_IOKIT_IOKITLIB_H
  kern_return_t status;

  if (io_master_port != MACH_PORT_NULL) {
    mach_port_deallocate(mach_task_self(), io_master_port);
    io_master_port = MACH_PORT_NULL;
  }

  status = IOMasterPort(MACH_PORT_NULL, &io_master_port);
  if (status != kIOReturnSuccess) {
    ERROR("IOMasterPort failed: %s", mach_error_string(status));
    io_master_port = MACH_PORT_NULL;
    return (-1);
  }
/* #endif HAVE_IOKIT_IOKITLIB_H */

#elif KERNEL_LINUX
#if HAVE_LIBUDEV
  if (conf_udev_name_attr != NULL) {
    handle_udev = udev_new();
    if (handle_udev == NULL) {
      ERROR("disk plugin: udev_new() failed!");
      return (-1);
    }
  }
#endif /* HAVE_LIBUDEV */
/* #endif KERNEL_LINUX */

#elif KERNEL_FREEBSD
  int rv;

  rv = geom_gettree(&geom_tree);
  if (rv != 0) {
    ERROR("geom_gettree() failed, returned %d", rv);
    return (-1);
  }
  rv = geom_stats_open();
  if (rv != 0) {
    ERROR("geom_stats_open() failed, returned %d", rv);
    return (-1);
  }
/* #endif KERNEL_FREEBSD */

#elif HAVE_LIBKSTAT
  kstat_t *ksp_chain;

  numdisk = 0;

  if (kc == NULL)
    return (-1);

  for (numdisk = 0, ksp_chain = kc->kc_chain;
       (numdisk < MAX_NUMDISK) && (ksp_chain != NULL);
       ksp_chain = ksp_chain->ks_next) {
    if (strncmp(ksp_chain->ks_class, "disk", 4) &&
        strncmp(ksp_chain->ks_class, "partition", 9))
      continue;
    if (ksp_chain->ks_type != KSTAT_TYPE_IO)
      continue;
    ksp[numdisk++] = ksp_chain;
  }
#endif /* HAVE_LIBKSTAT */

  return (0);
}
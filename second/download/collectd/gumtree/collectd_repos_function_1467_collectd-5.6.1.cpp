static int smart_read (void)
{
  struct udev *handle_udev;
  struct udev_enumerate *enumerate;
  struct udev_list_entry *devices, *dev_list_entry;
  struct udev_device *dev;

  /* Use udev to get a list of disks */
  handle_udev = udev_new();
  if (!handle_udev)
  {
    ERROR ("smart plugin: unable to initialize udev.");
    return (-1);
  }
  enumerate = udev_enumerate_new (handle_udev);
  udev_enumerate_add_match_subsystem (enumerate, "block");
  udev_enumerate_add_match_property (enumerate, "DEVTYPE", "disk");
  udev_enumerate_scan_devices (enumerate);
  devices = udev_enumerate_get_list_entry (enumerate);
  udev_list_entry_foreach (dev_list_entry, devices)
  {
    const char *path, *devpath, *serial;
    path = udev_list_entry_get_name (dev_list_entry);
    dev = udev_device_new_from_syspath (handle_udev, path);
    devpath = udev_device_get_devnode (dev);
    serial = udev_device_get_property_value (dev, "ID_SERIAL");

    /* Query status with libatasmart */
    smart_handle_disk (devpath, serial);
    udev_device_unref (dev);
  }

  udev_enumerate_unref (enumerate);
  udev_unref (handle_udev);

  return (0);
}
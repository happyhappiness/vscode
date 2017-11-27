static int ted_open_device(void) {
  const char *dev;
  struct termios options;

  if (fd >= 0)
    return (0);

  dev = DEFAULT_DEVICE;
  if (conf_device != NULL)
    dev = conf_device;

  fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
  if (fd < 0) {
    ERROR("ted plugin: Unable to open device %s.", dev);
    return (-1);
  }

  /* Get the current options for the port... */
  tcgetattr(fd, &options);
  options.c_cflag = B19200 | CS8 | CSTOPB | CREAD | CLOCAL;
  options.c_iflag = IGNBRK | IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  options.c_cc[VTIME] = 20;
  options.c_cc[VMIN] = 250;

  /* Set the new options for the port... */
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &options);

  INFO("ted plugin: Successfully opened %s.", dev);
  return (0);
}
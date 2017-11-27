static int ted_read(void) {
  double power;
  double voltage;
  int status;

  status = ted_open_device();
  if (status != 0)
    return (-1);

  power = NAN;
  voltage = NAN;
  for (int i = 0; i <= conf_retries; i++) {
    status = ted_read_value(&power, &voltage);
    if (status == 0)
      break;
  }

  if (status != 0)
    return (-1);

  ted_submit("power", power);
  ted_submit("voltage", voltage);

  return (0);
}
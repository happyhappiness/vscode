static int multimeter_read(void) {
  double value;

  if (fd < 0)
    return (-1);

  if (multimeter_read_value(&value) != 0)
    return (-1);

  multimeter_submit(value);
  return (0);
}
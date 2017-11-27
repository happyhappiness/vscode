static int cow_init (void)
{
  int status;

  if (device_g == NULL)
  {
    ERROR ("onewire plugin: cow_init: No device configured.");
    return (-1);
  }

  status = (int) OW_init (device_g);
  if (status != 0)
  {
    ERROR ("onewire plugin: OW_init(%s) failed: %i.", device_g, status);
    return (1);
  }

  return (0);
}
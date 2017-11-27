static int cow_shutdown (void)
{
  OW_finish ();
  ignorelist_free (sensor_list);
  return (0);
}
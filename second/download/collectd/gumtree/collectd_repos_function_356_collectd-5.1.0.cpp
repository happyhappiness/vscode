static int numa_read (void) /* {{{ */
{
  int i;
  int status;
  int success;

  if (max_node < 0)
  {
    WARNING ("numa plugin: No NUMA nodes were detected.");
    return (-1);
  }

  success = 0;
  for (i = 0; i <= max_node; i++)
  {
    status = numa_read_node (i);
    if (status == 0)
      success++;
  }

  return (success ? 0 : -1);
}
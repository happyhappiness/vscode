static int protocols_read(void) {
  int status;
  int success = 0;

  status = read_file(SNMP_FILE);
  if (status == 0)
    success++;

  status = read_file(NETSTAT_FILE);
  if (status == 0)
    success++;

  if (success == 0)
    return (-1);

  return (0);
}
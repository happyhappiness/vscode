int handle_listval (FILE *fh, char **fields, int fields_num)
{
  char **names = NULL;
  time_t *times = NULL;
  size_t number = 0;
  size_t i;
  int status;

  if (fields_num != 1)
  {
    DEBUG ("command listval: us_handle_listval: Wrong number of fields: %i",
	fields_num);
    print_to_socket (fh, "-1 Wrong number of fields: Got %i, expected 1.\n",
	fields_num);
    return (-1);
  }

  status = uc_get_names (&names, &times, &number);
  if (status != 0)
  {
    DEBUG ("command listval: uc_get_names failed with status %i", status);
    print_to_socket (fh, "-1 uc_get_names failed.\n");
    return (-1);
  }

  print_to_socket (fh, "%i Value%s found\n",
      (int) number, (number == 1) ? "" : "s");
  for (i = 0; i < number; i++)
    print_to_socket (fh, "%u %s\n", (unsigned int) times[i], names[i]);

  return (0);
}
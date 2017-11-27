int handle_listval (FILE *fh, char *buffer)
{
  char *command;
  char **names = NULL;
  time_t *times = NULL;
  size_t number = 0;
  size_t i;
  int status;

  DEBUG ("utils_cmd_listval: handle_listval (fh = %p, buffer = %s);",
      (void *) fh, buffer);

  command = NULL;
  status = parse_string (&buffer, &command);
  if (status != 0)
  {
    print_to_socket (fh, "-1 Cannot parse command.\n");
    return (-1);
  }
  assert (command != NULL);

  if (strcasecmp ("LISTVAL", command) != 0)
  {
    print_to_socket (fh, "-1 Unexpected command: `%s'.\n", command);
    return (-1);
  }

  if (*buffer != 0)
  {
    print_to_socket (fh, "-1 Garbage after end of command: %s\n", buffer);
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
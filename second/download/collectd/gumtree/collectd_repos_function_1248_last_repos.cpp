int handle_putnotif(FILE *fh, char *buffer) {
  char *command;
  notification_t n = {0};
  int status;

  if ((fh == NULL) || (buffer == NULL))
    return -1;

  DEBUG("utils_cmd_putnotif: handle_putnotif (fh = %p, buffer = %s);",
        (void *)fh, buffer);

  command = NULL;
  status = parse_string(&buffer, &command);
  if (status != 0) {
    print_to_socket(fh, "-1 Cannot parse command.\n");
    return -1;
  }
  assert(command != NULL);

  if (strcasecmp("PUTNOTIF", command) != 0) {
    print_to_socket(fh, "-1 Unexpected command: `%s'.\n", command);
    return -1;
  }

  status = 0;
  while (*buffer != 0) {
    char *key;
    char *value;

    status = parse_option(&buffer, &key, &value);
    if (status != 0) {
      print_to_socket(fh, "-1 Malformed option.\n");
      break;
    }

    status = set_option(&n, key, value);
    if (status != 0) {
      print_to_socket(fh, "-1 Error parsing option `%s'\n", key);
      break;
    }
  } /* for (i) */

  /* Check for required fields and complain if anything is missing. */
  if ((status == 0) && (n.severity == 0)) {
    print_to_socket(fh, "-1 Option `severity' missing.\n");
    status = -1;
  }
  if ((status == 0) && (n.time == 0)) {
    print_to_socket(fh, "-1 Option `time' missing.\n");
    status = -1;
  }
  if ((status == 0) && (strlen(n.message) == 0)) {
    print_to_socket(fh, "-1 No message or message of length 0 given.\n");
    status = -1;
  }

  /* If status is still zero the notification is fine and we can finally
   * dispatch it. */
  if (status == 0) {
    plugin_dispatch_notification(&n);
    print_to_socket(fh, "0 Success\n");
  }

  return 0;
}
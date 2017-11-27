static int sysfs_file_to_buffer(char const *dir, /* {{{ */
                                char const *power_supply, char const *basename,
                                char *buffer, size_t buffer_size) {
  char filename[PATH_MAX];
  int status;

  snprintf(filename, sizeof(filename), "%s/%s/%s", dir, power_supply, basename);

  status = (int)read_file_contents(filename, buffer, buffer_size - 1);
  if (status < 0)
    return status;

  buffer[status] = '\0';

  strstripnewline(buffer);
  return 0;
}
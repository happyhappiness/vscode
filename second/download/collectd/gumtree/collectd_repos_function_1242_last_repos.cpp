static int read_nodes(void) {
  static const char sys_node[] = "/sys/devices/system/node";
  static const char node_string[] = "node";
  static const char sys_node_hugepages[] =
      "/sys/devices/system/node/%s/hugepages";
  DIR *dir;
  struct dirent *result;
  char path[PATH_MAX];

  dir = opendir(sys_node);
  if (dir == NULL) {
    ERROR("%s: cannot open directory %s", g_plugin_name, sys_node);
    return -1;
  }

  while ((result = readdir(dir)) != NULL) {
    if (strncmp(result->d_name, node_string, sizeof(node_string) - 1)) {
      /* not node dir */
      errno = 0;
      continue;
    }

    snprintf(path, sizeof(path), sys_node_hugepages, result->d_name);
    read_syshugepages(path, result->d_name);
    errno = 0;
  }

  /* Check if NULL return from readdir() was an error */
  if (errno != 0) {
    ERROR("%s: readdir failed", g_plugin_name);
    closedir(dir);
    return -1;
  }

  closedir(dir);
  return 0;
}
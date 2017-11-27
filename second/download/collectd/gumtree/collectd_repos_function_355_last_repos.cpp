static int numa_read_node(int node) /* {{{ */
{
  char path[PATH_MAX];
  FILE *fh;
  char buffer[128];
  int status;
  int success;

  snprintf(path, sizeof(path), NUMA_ROOT_DIR "/node%i/numastat", node);

  fh = fopen(path, "r");
  if (fh == NULL) {
    char errbuf[1024];
    ERROR("numa plugin: Reading node %i failed: open(%s): %s", node, path,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  success = 0;
  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *fields[4];
    value_t v;

    status = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (status != 2) {
      WARNING("numa plugin: Ignoring line with unexpected "
              "number of fields (node %i).",
              node);
      continue;
    }

    v.derive = 0;
    status = parse_value(fields[1], &v, DS_TYPE_DERIVE);
    if (status != 0)
      continue;

    numa_dispatch_value(node, fields[0], v);
    success++;
  }

  fclose(fh);
  return success ? 0 : -1;
}
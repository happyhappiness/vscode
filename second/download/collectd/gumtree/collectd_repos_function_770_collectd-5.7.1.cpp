static int cow_simple_read(void) {
  value_list_t vl = VALUE_LIST_INIT;
  char *buffer;
  size_t buffer_size;
  int status;
  char errbuf[1024];
  char *endptr;
  direct_access_element_t *traverse;

  /* traverse list and check entries */
  for (traverse = direct_list; traverse != NULL; traverse = traverse->next) {
    sstrncpy(vl.plugin, "onewire", sizeof(vl.plugin));
    sstrncpy(vl.plugin_instance, traverse->address, sizeof(vl.plugin_instance));

    status = OW_get(traverse->path, &buffer, &buffer_size);
    if (status < 0) {
      ERROR("onewire plugin: OW_get (%s) failed. status = %s;", traverse->path,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return (-1);
    }
    DEBUG("onewire plugin: Read onewire device %s as %s", traverse->path,
          buffer);

    endptr = NULL;
    gauge_t g = strtod(buffer, &endptr);
    if (endptr == NULL) {
      ERROR("onewire plugin: Buffer is not a number: %s", buffer);
      continue;
    }

    sstrncpy(vl.type, traverse->file, sizeof(vl.type));
    sstrncpy(vl.type_instance, "", sizeof(""));

    vl.values = &(value_t){.gauge = g};
    vl.values_len = 1;

    plugin_dispatch_values(&vl);
    free(buffer);
  } /* for (traverse) */

  return 0;
}
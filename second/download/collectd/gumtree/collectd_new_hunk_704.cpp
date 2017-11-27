  status = fcntl(csv_fd, F_SETLK, &fl);
  if (status != 0) {
    char errbuf[1024];
    ERROR("csv plugin: flock (%s) failed: %s", filename,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    fclose(csv);
    return -1;
  }

  fprintf(csv, "%s\n", values);

  /* The lock is implicitely released. I we don't release it explicitely
   * because the `FILE *' may need to flush a cache first */
  fclose(csv);

  return 0;
} /* int csv_write */

void module_register(void) {
  plugin_register_config("csv", csv_config, config_keys, config_keys_num);
  plugin_register_write("csv", csv_write, /* user_data = */ NULL);
} /* void module_register */

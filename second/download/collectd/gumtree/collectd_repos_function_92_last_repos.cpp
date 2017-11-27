static int get_disk_err(virDomainPtr domain) {
  /* Get preferred size of disk errors array */
  int disk_err_count = virDomainGetDiskErrors(domain, NULL, 0, 0);
  if (disk_err_count == -1) {
    ERROR(PLUGIN_NAME
          " plugin: failed to get preferred size of disk errors array");
    return -1;
  }

  DEBUG(PLUGIN_NAME
        " plugin: preferred size of disk errors array: %d for domain %s",
        disk_err_count, virDomainGetName(domain));
  virDomainDiskError disk_err[disk_err_count];

  disk_err_count = virDomainGetDiskErrors(domain, disk_err, disk_err_count, 0);
  if (disk_err_count == -1) {
    ERROR(PLUGIN_NAME " plugin: virDomainGetDiskErrors failed with status %d",
          disk_err_count);
    return -1;
  }

  DEBUG(PLUGIN_NAME " plugin: detected %d disk errors in domain %s",
        disk_err_count, virDomainGetName(domain));

  for (int i = 0; i < disk_err_count; ++i) {
    disk_err_submit(domain, &disk_err[i]);
    sfree(disk_err[i].disk);
  }

  return 0;
}
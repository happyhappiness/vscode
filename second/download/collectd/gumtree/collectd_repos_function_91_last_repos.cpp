static void disk_err_submit(virDomainPtr domain,
                            virDomainDiskErrorPtr disk_err) {
  submit(domain, "disk_error", disk_err->disk,
         &(value_t){.gauge = disk_err->error}, 1);
}
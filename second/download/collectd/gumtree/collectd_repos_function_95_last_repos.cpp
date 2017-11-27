static int get_fs_info(virDomainPtr domain) {
  virDomainFSInfoPtr *fs_info = NULL;
  int ret = 0;

  int mount_points_cnt = virDomainGetFSInfo(domain, &fs_info, 0);
  if (mount_points_cnt == -1) {
    ERROR(PLUGIN_NAME " plugin: virDomainGetFSInfo failed: %d",
          mount_points_cnt);
    return mount_points_cnt;
  }

  for (int i = 0; i < mount_points_cnt; ++i) {
    if (fs_info_notify(domain, fs_info[i]) != 0) {
      ERROR(PLUGIN_NAME " plugin: failed to send file system notification "
                        "for mount point %s",
            fs_info[i]->mountpoint);
      ret = -1;
    }
    virDomainFSInfoFree(fs_info[i]);
  }

  sfree(fs_info);
  return ret;
}
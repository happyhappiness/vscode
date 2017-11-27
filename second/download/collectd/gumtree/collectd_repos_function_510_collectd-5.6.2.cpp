static int nfs_submit_fields_safe(int nfs_version, const char *instance,
                                  char **fields, size_t fields_num,
                                  const char **proc_names,
                                  size_t proc_names_num) {
  if (fields_num != proc_names_num) {
    WARNING("nfs plugin: Wrong number of fields for "
            "NFSv%i %s statistics. Expected %zu, got %zu.",
            nfs_version, instance, proc_names_num, fields_num);
    return (EINVAL);
  }

  nfs_submit_fields(nfs_version, instance, fields, fields_num, proc_names);

  return (0);
}
static int nfs_read_kstat(kstat_t *ksp, int nfs_version, const char *inst,
                          char const **proc_names, size_t proc_names_num) {
  char plugin_instance[DATA_MAX_NAME_LEN];
  value_t values[proc_names_num];

  if (ksp == NULL)
    return EINVAL;

  snprintf(plugin_instance, sizeof(plugin_instance), "v%i%s", nfs_version,
           inst);

  kstat_read(kc, ksp, NULL);
  for (size_t i = 0; i < proc_names_num; i++) {
    /* The name passed to kstat_data_lookup() doesn't have the
     * "const" modifier, so we need to copy the name here. */
    char name[32];
    sstrncpy(name, proc_names[i], sizeof(name));

    values[i].counter = (derive_t)get_kstat_value(ksp, name);
  }

  nfs_procedures_submit(plugin_instance, proc_names, values, proc_names_num);
  return 0;
}
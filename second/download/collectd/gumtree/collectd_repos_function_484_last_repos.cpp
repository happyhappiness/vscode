static int nfs_submit_nfs4_server(const char *instance, char **fields,
                                  size_t fields_num) {
  static int suppress_warning = 0;
  size_t proc4x_names_num;

  switch (fields_num) {
  case NFS4_SERVER40_NUM_PROC:
  case NFS4_SERVER40_NUM_PROC + 19: /* NFS 4.1 */
  case NFS4_SERVER40_NUM_PROC + 31: /* NFS 4.2 */
  case NFS4_SERVER40_NUM_PROC + 32: /* NFS 4.2 */
    break;
  default:
    if (!suppress_warning) {
      WARNING("nfs plugin: Unexpected number of fields for "
              "NFSv4 %s statistics: %zu. ",
              instance, fields_num);
    }

    if (fields_num > NFS4_SERVER_MAX_PROC) {
      fields_num = NFS4_SERVER_MAX_PROC;
      suppress_warning = 1;
    } else {
      return EINVAL;
    }
  }

  nfs_submit_fields(4, instance, fields, nfs4_server40_procedures_names_num,
                    nfs4_server40_procedures_names);

  if (fields_num > nfs4_server40_procedures_names_num) {
    proc4x_names_num = fields_num - nfs4_server40_procedures_names_num;
    fields += nfs4_server40_procedures_names_num;

    nfs_submit_fields(4, instance, fields, proc4x_names_num,
                      nfs4_server4x_procedures_names);
  }

  return 0;
}
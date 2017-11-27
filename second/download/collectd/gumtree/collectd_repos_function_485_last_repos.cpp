static int nfs_submit_nfs4_client(const char *instance, char **fields,
                                  size_t fields_num) {
  size_t proc40_names_num, proc4x_names_num;

  static int suppress_warning = 0;

  switch (fields_num) {
  case 34:
  case 35:
  case 36:
  case 37:
  case 38:
    /* 4.0-only configuration */
    proc40_names_num = fields_num;
    break;
  case 40:
  case 41:
    proc40_names_num = 35;
    break;
  case 42:
  case 44:
    proc40_names_num = 36;
    break;
  case 46:
  case 47:
  case 51:
  case 53:
    proc40_names_num = 37;
    break;
  case 54:
  case 55:
  case 57:
  case 58:
  case 59:
  case 60:
    proc40_names_num = 38;
    break;
  default:
    if (!suppress_warning) {
      WARNING("nfs plugin: Unexpected number of "
              "fields for NFSv4 %s "
              "statistics: %zu. ",
              instance, fields_num);
    }

    if (fields_num > 34) {
      /* safe fallback to basic nfs40 procedures */
      fields_num = 34;
      proc40_names_num = 34;

      suppress_warning = 1;
    } else {
      return EINVAL;
    }
  }

  nfs_submit_fields(4, instance, fields, proc40_names_num,
                    nfs4_client40_procedures_names);

  if (fields_num > proc40_names_num) {
    proc4x_names_num = fields_num - proc40_names_num;
    fields += proc40_names_num;

    nfs_submit_fields(4, instance, fields, proc4x_names_num,
                      nfs4_client4x_procedures_names);
  }

  return 0;
}
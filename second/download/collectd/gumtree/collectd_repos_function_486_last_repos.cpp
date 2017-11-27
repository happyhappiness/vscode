static void nfs_read_linux(FILE *fh, const char *inst) {
  char buffer[1024];

  char *fields[64];
  int fields_num = 0;

  if (fh == NULL)
    return;

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    fields_num = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));

    if (fields_num < 3)
      continue;

    if (strcmp(fields[0], "proc2") == 0 && report_v2) {
      nfs_submit_fields_safe(/* version = */ 2, inst, fields + 2,
                             (size_t)(fields_num - 2), nfs2_procedures_names,
                             nfs2_procedures_names_num);
    } else if (strncmp(fields[0], "proc3", 5) == 0 && report_v3) {
      nfs_submit_fields_safe(/* version = */ 3, inst, fields + 2,
                             (size_t)(fields_num - 2), nfs3_procedures_names,
                             nfs3_procedures_names_num);
    } else if (strcmp(fields[0], "proc4ops") == 0 && report_v4) {
      if (inst[0] == 's')
        nfs_submit_nfs4_server(inst, fields + 2, (size_t)(fields_num - 2));
    } else if (strcmp(fields[0], "proc4") == 0 && report_v4) {
      if (inst[0] == 'c')
        nfs_submit_nfs4_client(inst, fields + 2, (size_t)(fields_num - 2));
    }
  } /* while (fgets) */
}
static int nfs_read(void) {
  if (report_v2) {
    nfs_read_kstat(nfs2_ksp_client, /* version = */ 2, "client",
                   nfs2_procedures_names, nfs2_procedures_names_num);
    nfs_read_kstat(nfs2_ksp_server, /* version = */ 2, "server",
                   nfs2_procedures_names, nfs2_procedures_names_num);
  }
  if (report_v3) {
    nfs_read_kstat(nfs3_ksp_client, /* version = */ 3, "client",
                   nfs3_procedures_names, nfs3_procedures_names_num);
    nfs_read_kstat(nfs3_ksp_server, /* version = */ 3, "server",
                   nfs3_procedures_names, nfs3_procedures_names_num);
  }
  if (report_v4) {
    nfs_read_kstat(nfs4_ksp_client, /* version = */ 4, "client",
                   nfs4_procedures_names, nfs4_procedures_names_num);
    nfs_read_kstat(nfs4_ksp_server, /* version = */ 4, "server",
                   nfs4_procedures_names, nfs4_procedures_names_num);
  }

  return 0;
}
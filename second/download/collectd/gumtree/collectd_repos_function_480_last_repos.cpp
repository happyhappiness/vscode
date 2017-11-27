static int nfs_init(void) {
  nfs2_ksp_client = NULL;
  nfs2_ksp_server = NULL;
  nfs3_ksp_client = NULL;
  nfs3_ksp_server = NULL;
  nfs4_ksp_client = NULL;
  nfs4_ksp_server = NULL;

  if (kc == NULL)
    return -1;

  for (kstat_t *ksp_chain = kc->kc_chain; ksp_chain != NULL;
       ksp_chain = ksp_chain->ks_next) {
    if (strncmp(ksp_chain->ks_module, "nfs", 3) != 0)
      continue;
    else if (strncmp(ksp_chain->ks_name, "rfsproccnt_v2", 13) == 0)
      nfs2_ksp_server = ksp_chain;
    else if (strncmp(ksp_chain->ks_name, "rfsproccnt_v3", 13) == 0)
      nfs3_ksp_server = ksp_chain;
    else if (strncmp(ksp_chain->ks_name, "rfsproccnt_v4", 13) == 0)
      nfs4_ksp_server = ksp_chain;
    else if (strncmp(ksp_chain->ks_name, "rfsreqcnt_v2", 12) == 0)
      nfs2_ksp_client = ksp_chain;
    else if (strncmp(ksp_chain->ks_name, "rfsreqcnt_v3", 12) == 0)
      nfs3_ksp_client = ksp_chain;
    else if (strncmp(ksp_chain->ks_name, "rfsreqcnt_v4", 12) == 0)
      nfs4_ksp_client = ksp_chain;
  }

  return 0;
}
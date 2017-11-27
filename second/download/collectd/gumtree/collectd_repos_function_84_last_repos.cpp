static int lv_domain_block_info(virDomainPtr dom, const char *path,
                                struct lv_block_info *binfo) {
#ifdef HAVE_BLOCK_STATS_FLAGS
  int nparams = 0;
  if (virDomainBlockStatsFlags(dom, path, NULL, &nparams, 0) < 0 ||
      nparams <= 0) {
    VIRT_ERROR(conn, "getting the disk params count");
    return -1;
  }

  virTypedParameterPtr params = calloc((size_t)nparams, sizeof(*params));
  if (params == NULL) {
    ERROR("virt plugin: alloc(%i) for block=%s parameters failed.", nparams,
          path);
    return -1;
  }

  int rc = -1;
  if (virDomainBlockStatsFlags(dom, path, params, &nparams, 0) < 0) {
    VIRT_ERROR(conn, "getting the disk params values");
  } else {
    rc = get_block_info(binfo, params, nparams);
  }

  virTypedParamsClear(params, nparams);
  sfree(params);
  return rc;
#else
  return virDomainBlockStats(dom, path, &(binfo->bi), sizeof(binfo->bi));
#endif /* HAVE_BLOCK_STATS_FLAGS */
}
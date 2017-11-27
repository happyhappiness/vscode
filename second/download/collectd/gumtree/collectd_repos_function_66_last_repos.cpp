static int lv_domain_info(virDomainPtr dom, struct lv_info *info) {
#ifdef HAVE_CPU_STATS
  virTypedParameterPtr param = NULL;
  int nparams = 0;
#endif /* HAVE_CPU_STATS */
  int ret = virDomainGetInfo(dom, &(info->di));
  if (ret != 0) {
    return ret;
  }

#ifdef HAVE_CPU_STATS
  nparams = virDomainGetCPUStats(dom, NULL, 0, -1, 1, 0);
  if (nparams < 0) {
    VIRT_ERROR(conn, "getting the CPU params count");
    return -1;
  }

  param = calloc(nparams, sizeof(virTypedParameter));
  if (param == NULL) {
    ERROR("virt plugin: alloc(%i) for cpu parameters failed.", nparams);
    return -1;
  }

  ret = virDomainGetCPUStats(dom, param, nparams, -1, 1, 0); // total stats.
  if (ret < 0) {
    virTypedParamsClear(param, nparams);
    sfree(param);
    VIRT_ERROR(conn, "getting the disk params values");
    return -1;
  }

  for (int i = 0; i < nparams; ++i) {
    if (!strcmp(param[i].field, "user_time"))
      info->total_user_cpu_time = param[i].value.ul;
    else if (!strcmp(param[i].field, "system_time"))
      info->total_syst_cpu_time = param[i].value.ul;
  }

  virTypedParamsClear(param, nparams);
  sfree(param);
#endif /* HAVE_CPU_STATS */

  return 0;
}
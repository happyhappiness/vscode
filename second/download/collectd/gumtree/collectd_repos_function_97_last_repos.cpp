static int get_job_stats(virDomainPtr domain) {
  int ret = 0;
  int job_type = 0;
  int nparams = 0;
  virTypedParameterPtr params = NULL;
  int flags = (extra_stats & ex_stats_job_stats_completed)
                  ? VIR_DOMAIN_JOB_STATS_COMPLETED
                  : 0;

  ret = virDomainGetJobStats(domain, &job_type, &params, &nparams, flags);
  if (ret != 0) {
    ERROR(PLUGIN_NAME " plugin: virDomainGetJobStats failed: %d", ret);
    return ret;
  }

  DEBUG(PLUGIN_NAME " plugin: job_type=%d nparams=%d", job_type, nparams);

  for (int i = 0; i < nparams; ++i) {
    DEBUG(PLUGIN_NAME " plugin: param[%d] field=%s type=%d", i, params[i].field,
          params[i].type);
    job_stats_submit(domain, &params[i]);
  }

  virTypedParamsFree(params, nparams);
  return ret;
}
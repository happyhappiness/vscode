static void perf_submit(virDomainStatsRecordPtr stats) {
  for (int i = 0; i < stats->nparams; ++i) {
    /* Replace '.' with '_' in event field to match other metrics' naming
     * convention */
    char *c = strchr(stats->params[i].field, '.');
    if (c)
      *c = '_';
    submit(stats->dom, "perf", stats->params[i].field,
           &(value_t){.derive = stats->params[i].value.ul}, 1);
  }
}
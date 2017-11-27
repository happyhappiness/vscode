void latency_config_free(latency_config_t conf) {
  sfree(conf.percentile);
  sfree(conf.buckets);
}
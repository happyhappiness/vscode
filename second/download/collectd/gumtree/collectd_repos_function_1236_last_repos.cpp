int latency_config_copy(latency_config_t *dst, const latency_config_t src) {
  *dst = (latency_config_t){
      .percentile_num = src.percentile_num, .buckets_num = src.buckets_num,
  };

  dst->percentile = calloc(dst->percentile_num, sizeof(*dst->percentile));
  dst->buckets = calloc(dst->buckets_num, sizeof(*dst->buckets));

  if ((dst->percentile == NULL) || (dst->buckets == NULL)) {
    latency_config_free(*dst);
    return ENOMEM;
  }

  if (src.bucket_type != NULL) {
    dst->bucket_type = strdup(src.bucket_type);
    if (dst->bucket_type == NULL) {
      latency_config_free(*dst);
      return ENOMEM;
    }
  }

  memmove(dst->percentile, src.percentile,
          dst->percentile_num * sizeof(*dst->percentile));
  memmove(dst->buckets, src.buckets, dst->buckets_num * sizeof(*dst->buckets));

  return 0;
}
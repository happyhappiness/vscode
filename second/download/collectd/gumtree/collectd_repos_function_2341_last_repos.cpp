static cdtime_t new_random_ttl() {
  if (resolve_jitter == 0)
    return 0;

  return (cdtime_t)cdrand_range(0, (long)resolve_jitter);
}
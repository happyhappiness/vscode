uint32_t cdrand_u() {
  long r;

  pthread_mutex_lock(&lock);
  cdrand_seed();
  r = jrand48(seed);
  pthread_mutex_unlock(&lock);

  return (uint32_t)r;
}
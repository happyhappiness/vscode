double cdrand_d() {
  double r;

  pthread_mutex_lock(&lock);
  cdrand_seed();
  r = erand48(seed);
  pthread_mutex_unlock(&lock);

  return (r);
}
long cdrand_range(long min, long max) {
  long range;
  long r;

  range = 1 + max - min;

  r = (long)(0.5 + (cdrand_d() * range));
  r += min;

  return r;
}
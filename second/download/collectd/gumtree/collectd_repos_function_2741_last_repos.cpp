static void cdrand_seed(void) {
  cdtime_t t;

  if (have_seed)
    return;

  t = cdtime();

  seed[0] = (unsigned short)t;
  seed[1] = (unsigned short)(t >> 16);
  seed[2] = (unsigned short)(t >> 32);

  have_seed = 1;
}
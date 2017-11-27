static int process_device(int sk, const char *dev) {
  int num_success = 0;
  int status;

  status = process_athstats(sk, dev);
  if (status == 0)
    num_success++;

  status = process_80211stats(sk, dev);
  if (status == 0)
    num_success++;

  status = process_stations(sk, dev);
  if (status == 0)
    num_success++;

  return (num_success == 0) ? -1 : 0;
}
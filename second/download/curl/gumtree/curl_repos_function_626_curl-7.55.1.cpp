static bool usec_matches_seconds(time_t time_usec, int expected_seconds)
{
  int time_sec = (int)(time_usec / usec_magnitude);
  bool same = (time_sec == expected_seconds);
  fprintf(stderr, "is %d us same as %d seconds? %s\n",
          (int)time_usec, expected_seconds,
          same?"Yes":"No");
  return same;
}
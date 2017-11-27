static int get_boundet_random(int min, int max) /* {{{ */
{
  int range;

  if (min >= max)
    return (-1);
  if (min == (max - 1))
    return (min);

  range = max - min;

  return (min + ((int)(((double)range) * ((double)random()) /
                       (((double)RAND_MAX) + 1.0))));
}
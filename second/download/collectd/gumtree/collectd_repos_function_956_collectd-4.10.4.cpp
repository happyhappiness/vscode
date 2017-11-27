static void float_counter_add (float_counter_t *fc, float val) /* {{{ */
{
  uint64_t tmp;

  if (val < 0.0)
    return;

  tmp = (uint64_t) val;
  val -= (double) tmp;

  fc->i += tmp;
  fc->n += (uint64_t) ((val * 1000000000.0) + .5);

  if (fc->n >= 1000000000)
  {
    fc->i += 1;
    fc->n -= 1000000000;
    assert (fc->n < 1000000000);
  }
}
static gauge_t calculate_ratio_percent2(derive_t part1, derive_t part2,
                                        derive_t *prev1, derive_t *prev2) {
  if ((*prev1 == 0) || (*prev2 == 0) || (part1 < *prev1) || (part2 < *prev2)) {
    *prev1 = part1;
    *prev2 = part2;
    return NAN;
  }

  derive_t num = part1 - *prev1;
  derive_t denom = part2 - *prev2 + num;

  *prev1 = part1;
  *prev2 = part2;

  if (denom == 0)
    return NAN;

  if (num == 0)
    return 0;

  return 100.0 * (gauge_t)num / (gauge_t)denom;
}
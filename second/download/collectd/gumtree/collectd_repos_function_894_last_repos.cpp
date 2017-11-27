static gauge_t calculate_ratio_percent(derive_t part, derive_t total,
                                       derive_t *prev_part,
                                       derive_t *prev_total) {
  if ((*prev_part == 0) || (*prev_total == 0) || (part < *prev_part) ||
      (total < *prev_total)) {
    *prev_part = part;
    *prev_total = total;
    return NAN;
  }

  derive_t num = part - *prev_part;
  derive_t denom = total - *prev_total;

  *prev_part = part;
  *prev_total = total;

  if (denom == 0)
    return NAN;

  if (num == 0)
    return 0;

  return 100.0 * (gauge_t)num / (gauge_t)denom;
}
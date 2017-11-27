counter_t counter_diff(counter_t old_value, counter_t new_value) {
  counter_t diff;

  if (old_value > new_value) {
    if (old_value <= 4294967295U)
      diff = (4294967295U - old_value) + new_value + 1;
    else
      diff = (18446744073709551615ULL - old_value) + new_value + 1;
  } else {
    diff = new_value - old_value;
  }

  return (diff);
}
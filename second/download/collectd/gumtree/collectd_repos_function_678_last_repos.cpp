static void ps_update_counter(derive_t *group_counter, derive_t *curr_counter,
                              derive_t new_counter) {
  unsigned long curr_value;

  if (want_init) {
    *curr_counter = new_counter;
    return;
  }

  if (new_counter < *curr_counter)
    curr_value = new_counter + (ULONG_MAX - *curr_counter);
  else
    curr_value = new_counter - *curr_counter;

  if (*group_counter == -1)
    *group_counter = 0;

  *curr_counter = new_counter;
  *group_counter += curr_value;
}
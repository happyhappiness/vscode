static int madwifi_real_init(void) {
  size_t max = STATIC_ARRAY_SIZE(specs);

  for (size_t i = 0; i < STATIC_ARRAY_SIZE(bounds); i++)
    bounds[i] = 0;

  watchlist_set(watch_items, 0);
  watchlist_set(misc_items, 0);

  for (size_t i = 0; i < max; i++) {
    bounds[specs[i].flags & SRC_MASK] = i;

    if (specs[i].flags & LOG)
      watch_items[i / 32] |= FLAG(i);

    if (specs[i].flags & SU)
      misc_items[i / 32] |= FLAG(i);
  }

  for (size_t i = 0; i < STATIC_ARRAY_SIZE(bounds); i++)
    bounds[i]++;

  return 0;
}
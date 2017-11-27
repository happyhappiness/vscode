static inline int item_watched(int i) {
  assert(i >= 0);
  assert((size_t)i < (STATIC_ARRAY_SIZE(watch_items) * 32));
  return watch_items[i / 32] & FLAG(i);
}
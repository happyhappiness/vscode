static inline int item_summed(int i) {
  assert(i >= 0);
  assert((size_t)i < (STATIC_ARRAY_SIZE(misc_items) * 32));
  return misc_items[i / 32] & FLAG(i);
}
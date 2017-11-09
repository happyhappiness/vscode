int dlmalloc_trim(size_t pad) {
  ensure_initialization();
  int result = 0;
  if (!PREACTION(gm)) {
    result = sys_trim(gm, pad);
    POSTACTION(gm);
  }
  return result;
}
static void do_check_inuse_chunk(mstate m, mchunkptr p) {
  do_check_any_chunk(m, p);
  assert(cinuse(p));
  assert(next_pinuse(p));
  /* If not pinuse and not mmapped, previous chunk has OK offset */
  assert(is_mmapped(p) || pinuse(p) || next_chunk(prev_chunk(p)) == p);
  if (is_mmapped(p))
    do_check_mmapped_chunk(m, p);
}
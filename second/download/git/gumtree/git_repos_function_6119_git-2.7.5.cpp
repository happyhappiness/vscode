static void do_check_any_chunk(mstate m, mchunkptr p) {
  assert((is_aligned(chunk2mem(p))) || (p->head == FENCEPOST_HEAD));
  assert(ok_address(m, p));
}
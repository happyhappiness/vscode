static void do_check_mmapped_chunk(mstate m, mchunkptr p) {
  size_t  sz = chunksize(p);
  size_t len = (sz + (p->prev_foot & ~IS_MMAPPED_BIT) + MMAP_FOOT_PAD);
  assert(is_mmapped(p));
  assert(use_mmap(m));
  assert((is_aligned(chunk2mem(p))) || (p->head == FENCEPOST_HEAD));
  assert(ok_address(m, p));
  assert(!is_small(sz));
  assert((len & (mparams.page_size-SIZE_T_ONE)) == 0);
  assert(chunk_plus_offset(p, sz)->head == FENCEPOST_HEAD);
  assert(chunk_plus_offset(p, sz+SIZE_T_SIZE)->head == 0);
}
static void do_check_smallbin(mstate m, bindex_t i) {
  sbinptr b = smallbin_at(m, i);
  mchunkptr p = b->bk;
  unsigned int empty = (m->smallmap & (1U << i)) == 0;
  if (p == b)
    assert(empty);
  if (!empty) {
    for (; p != b; p = p->bk) {
      size_t size = chunksize(p);
      mchunkptr q;
      /* each chunk claims to be free */
      do_check_free_chunk(m, p);
      /* chunk belongs in bin */
      assert(small_index(size) == i);
      assert(p->bk == b || chunksize(p->bk) == chunksize(p));
      /* chunk is followed by an inuse chunk */
      q = next_chunk(p);
      if (q->head != FENCEPOST_HEAD)
	do_check_inuse_chunk(m, q);
    }
  }
}
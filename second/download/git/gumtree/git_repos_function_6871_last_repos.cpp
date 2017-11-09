static size_t traverse_and_check(mstate m) {
  size_t sum = 0;
  if (is_initialized(m)) {
    msegmentptr s = &m->seg;
    sum += m->topsize + TOP_FOOT_SIZE;
    while (s != 0) {
      mchunkptr q = align_as_chunk(s->base);
      mchunkptr lastq = 0;
      assert(pinuse(q));
      while (segment_holds(s, q) &&
	     q != m->top && q->head != FENCEPOST_HEAD) {
	sum += chunksize(q);
	if (cinuse(q)) {
	  assert(!bin_find(m, q));
	  do_check_inuse_chunk(m, q);
	}
	else {
	  assert(q == m->dv || bin_find(m, q));
	  assert(lastq == 0 || cinuse(lastq)); /* Not 2 consecutive free */
	  do_check_free_chunk(m, q);
	}
	lastq = q;
	q = next_chunk(q);
      }
      s = s->next;
    }
  }
  return sum;
}
static void internal_malloc_stats(mstate m) {
  ensure_initialization();
  if (!PREACTION(m)) {
    size_t maxfp = 0;
    size_t fp = 0;
    size_t used = 0;
    check_malloc_state(m);
    if (is_initialized(m)) {
      msegmentptr s = &m->seg;
      maxfp = m->max_footprint;
      fp = m->footprint;
      used = fp - (m->topsize + TOP_FOOT_SIZE);

      while (s != 0) {
	mchunkptr q = align_as_chunk(s->base);
	while (segment_holds(s, q) &&
	       q != m->top && q->head != FENCEPOST_HEAD) {
	  if (!cinuse(q))
	    used -= chunksize(q);
	  q = next_chunk(q);
	}
	s = s->next;
      }
    }

    fprintf(stderr, "max system bytes = %10lu\n", (unsigned long)(maxfp));
    fprintf(stderr, "system bytes     = %10lu\n", (unsigned long)(fp));
    fprintf(stderr, "in use bytes     = %10lu\n", (unsigned long)(used));

    POSTACTION(m);
  }
}
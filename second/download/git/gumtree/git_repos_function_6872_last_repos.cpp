static void do_check_malloc_state(mstate m) {
  bindex_t i;
  size_t total;
  /* check bins */
  for (i = 0; i < NSMALLBINS; ++i)
    do_check_smallbin(m, i);
  for (i = 0; i < NTREEBINS; ++i)
    do_check_treebin(m, i);

  if (m->dvsize != 0) { /* check dv chunk */
    do_check_any_chunk(m, m->dv);
    assert(m->dvsize == chunksize(m->dv));
    assert(m->dvsize >= MIN_CHUNK_SIZE);
    assert(bin_find(m, m->dv) == 0);
  }

  if (m->top != 0) {   /* check top chunk */
    do_check_top_chunk(m, m->top);
    /*assert(m->topsize == chunksize(m->top)); redundant */
    assert(m->topsize > 0);
    assert(bin_find(m, m->top) == 0);
  }

  total = traverse_and_check(m);
  assert(total <= m->footprint);
  assert(m->footprint <= m->max_footprint);
}
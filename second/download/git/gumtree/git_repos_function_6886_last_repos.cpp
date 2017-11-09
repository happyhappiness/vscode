static void* tmalloc_small(mstate m, size_t nb) {
  tchunkptr t, v;
  size_t rsize;
  bindex_t i;
  binmap_t leastbit = least_bit(m->treemap);
  compute_bit2idx(leastbit, i);
  v = t = *treebin_at(m, i);
  rsize = chunksize(t) - nb;

  while ((t = leftmost_child(t)) != 0) {
    size_t trem = chunksize(t) - nb;
    if (trem < rsize) {
      rsize = trem;
      v = t;
    }
  }

  if (RTCHECK(ok_address(m, v))) {
    mchunkptr r = chunk_plus_offset(v, nb);
    assert(chunksize(v) == rsize + nb);
    if (RTCHECK(ok_next(v, r))) {
      unlink_large_chunk(m, v);
      if (rsize < MIN_CHUNK_SIZE)
	set_inuse_and_pinuse(m, v, (rsize + nb));
      else {
	set_size_and_pinuse_of_inuse_chunk(m, v, nb);
	set_size_and_pinuse_of_free_chunk(r, rsize);
	replace_dv(m, r, rsize);
      }
      return chunk2mem(v);
    }
  }

  CORRUPTION_ERROR_ACTION(m);
  return 0;
}
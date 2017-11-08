static void* internal_realloc(mstate m, void* oldmem, size_t bytes) {
  if (bytes >= MAX_REQUEST) {
    MALLOC_FAILURE_ACTION;
    return 0;
  }
  if (!PREACTION(m)) {
    mchunkptr oldp = mem2chunk(oldmem);
    size_t oldsize = chunksize(oldp);
    mchunkptr next = chunk_plus_offset(oldp, oldsize);
    mchunkptr newp = 0;
    void* extra = 0;

    /* Try to either shrink or extend into top. Else malloc-copy-free */

    if (RTCHECK(ok_address(m, oldp) && ok_cinuse(oldp) &&
		ok_next(oldp, next) && ok_pinuse(next))) {
      size_t nb = request2size(bytes);
      if (is_mmapped(oldp))
	newp = mmap_resize(m, oldp, nb);
      else if (oldsize >= nb) { /* already big enough */
	size_t rsize = oldsize - nb;
	newp = oldp;
	if (rsize >= MIN_CHUNK_SIZE) {
	  mchunkptr remainder = chunk_plus_offset(newp, nb);
	  set_inuse(m, newp, nb);
	  set_inuse(m, remainder, rsize);
	  extra = chunk2mem(remainder);
	}
      }
      else if (next == m->top && oldsize + m->topsize > nb) {
	/* Expand into top */
	size_t newsize = oldsize + m->topsize;
	size_t newtopsize = newsize - nb;
	mchunkptr newtop = chunk_plus_offset(oldp, nb);
	set_inuse(m, oldp, nb);
	newtop->head = newtopsize |PINUSE_BIT;
	m->top = newtop;
	m->topsize = newtopsize;
	newp = oldp;
      }
    }
    else {
      USAGE_ERROR_ACTION(m, oldmem);
      POSTACTION(m);
      return 0;
    }

    POSTACTION(m);

    if (newp != 0) {
      if (extra != 0) {
	internal_free(m, extra);
      }
      check_inuse_chunk(m, newp);
      return chunk2mem(newp);
    }
    else {
      void* newmem = internal_malloc(m, bytes);
      if (newmem != 0) {
	size_t oc = oldsize - overhead_for(oldp);
	memcpy(newmem, oldmem, (oc < bytes)? oc : bytes);
	internal_free(m, oldmem);
      }
      return newmem;
    }
  }
  return 0;
}
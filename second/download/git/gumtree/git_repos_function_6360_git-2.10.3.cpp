static void* internal_memalign(mstate m, size_t alignment, size_t bytes) {
  if (alignment <= MALLOC_ALIGNMENT)    /* Can just use malloc */
    return internal_malloc(m, bytes);
  if (alignment <  MIN_CHUNK_SIZE) /* must be at least a minimum chunk size */
    alignment = MIN_CHUNK_SIZE;
  if ((alignment & (alignment-SIZE_T_ONE)) != 0) {/* Ensure a power of 2 */
    size_t a = MALLOC_ALIGNMENT << 1;
    while (a < alignment) a <<= 1;
    alignment = a;
  }

  if (bytes >= MAX_REQUEST - alignment) {
    if (m != 0)  { /* Test isn't needed but avoids compiler warning */
      MALLOC_FAILURE_ACTION;
    }
  }
  else {
    size_t nb = request2size(bytes);
    size_t req = nb + alignment + MIN_CHUNK_SIZE - CHUNK_OVERHEAD;
    char* mem = (char*)internal_malloc(m, req);
    if (mem != 0) {
      void* leader = 0;
      void* trailer = 0;
      mchunkptr p = mem2chunk(mem);

      if (PREACTION(m)) return 0;
      if ((((size_t)(mem)) % alignment) != 0) { /* misaligned */
	/*
	  Find an aligned spot inside chunk.  Since we need to give
	  back leading space in a chunk of at least MIN_CHUNK_SIZE, if
	  the first calculation places us at a spot with less than
	  MIN_CHUNK_SIZE leader, we can move to the next aligned spot.
	  We've allocated enough total room so that this is always
	  possible.
	*/
	char* br = (char*)mem2chunk((size_t)(((size_t)(mem +
						       alignment -
						       SIZE_T_ONE)) &
					     -alignment));
	char* pos = ((size_t)(br - (char*)(p)) >= MIN_CHUNK_SIZE)?
	  br : br+alignment;
	mchunkptr newp = (mchunkptr)pos;
	size_t leadsize = pos - (char*)(p);
	size_t newsize = chunksize(p) - leadsize;

	if (is_mmapped(p)) { /* For mmapped chunks, just adjust offset */
	  newp->prev_foot = p->prev_foot + leadsize;
	  newp->head = (newsize|CINUSE_BIT);
	}
	else { /* Otherwise, give back leader, use the rest */
	  set_inuse(m, newp, newsize);
	  set_inuse(m, p, leadsize);
	  leader = chunk2mem(p);
	}
	p = newp;
      }

      /* Give back spare room at the end */
      if (!is_mmapped(p)) {
	size_t size = chunksize(p);
	if (size > nb + MIN_CHUNK_SIZE) {
	  size_t remainder_size = size - nb;
	  mchunkptr remainder = chunk_plus_offset(p, nb);
	  set_inuse(m, p, nb);
	  set_inuse(m, remainder, remainder_size);
	  trailer = chunk2mem(remainder);
	}
      }

      assert (chunksize(p) >= nb);
      assert((((size_t)(chunk2mem(p))) % alignment) == 0);
      check_inuse_chunk(m, p);
      POSTACTION(m);
      if (leader != 0) {
	internal_free(m, leader);
      }
      if (trailer != 0) {
	internal_free(m, trailer);
      }
      return chunk2mem(p);
    }
  }
  return 0;
}
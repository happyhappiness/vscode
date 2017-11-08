void* mspace_malloc(mspace msp, size_t bytes) {
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms,ms);
    return 0;
  }
  if (!PREACTION(ms)) {
    void* mem;
    size_t nb;
    if (bytes <= MAX_SMALL_REQUEST) {
      bindex_t idx;
      binmap_t smallbits;
      nb = (bytes < MIN_REQUEST)? MIN_CHUNK_SIZE : pad_request(bytes);
      idx = small_index(nb);
      smallbits = ms->smallmap >> idx;

      if ((smallbits & 0x3U) != 0) { /* Remainderless fit to a smallbin. */
	mchunkptr b, p;
	idx += ~smallbits & 1;       /* Uses next bin if idx empty */
	b = smallbin_at(ms, idx);
	p = b->fd;
	assert(chunksize(p) == small_index2size(idx));
	unlink_first_small_chunk(ms, b, p, idx);
	set_inuse_and_pinuse(ms, p, small_index2size(idx));
	mem = chunk2mem(p);
	check_malloced_chunk(ms, mem, nb);
	goto postaction;
      }

      else if (nb > ms->dvsize) {
	if (smallbits != 0) { /* Use chunk in next nonempty smallbin */
	  mchunkptr b, p, r;
	  size_t rsize;
	  bindex_t i;
	  binmap_t leftbits = (smallbits << idx) & left_bits(idx2bit(idx));
	  binmap_t leastbit = least_bit(leftbits);
	  compute_bit2idx(leastbit, i);
	  b = smallbin_at(ms, i);
	  p = b->fd;
	  assert(chunksize(p) == small_index2size(i));
	  unlink_first_small_chunk(ms, b, p, i);
	  rsize = small_index2size(i) - nb;
	  /* Fit here cannot be remainderless if 4byte sizes */
	  if (SIZE_T_SIZE != 4 && rsize < MIN_CHUNK_SIZE)
	    set_inuse_and_pinuse(ms, p, small_index2size(i));
	  else {
	    set_size_and_pinuse_of_inuse_chunk(ms, p, nb);
	    r = chunk_plus_offset(p, nb);
	    set_size_and_pinuse_of_free_chunk(r, rsize);
	    replace_dv(ms, r, rsize);
	  }
	  mem = chunk2mem(p);
	  check_malloced_chunk(ms, mem, nb);
	  goto postaction;
	}

	else if (ms->treemap != 0 && (mem = tmalloc_small(ms, nb)) != 0) {
	  check_malloced_chunk(ms, mem, nb);
	  goto postaction;
	}
      }
    }
    else if (bytes >= MAX_REQUEST)
      nb = MAX_SIZE_T; /* Too big to allocate. Force failure (in sys alloc) */
    else {
      nb = pad_request(bytes);
      if (ms->treemap != 0 && (mem = tmalloc_large(ms, nb)) != 0) {
	check_malloced_chunk(ms, mem, nb);
	goto postaction;
      }
    }

    if (nb <= ms->dvsize) {
      size_t rsize = ms->dvsize - nb;
      mchunkptr p = ms->dv;
      if (rsize >= MIN_CHUNK_SIZE) { /* split dv */
	mchunkptr r = ms->dv = chunk_plus_offset(p, nb);
	ms->dvsize = rsize;
	set_size_and_pinuse_of_free_chunk(r, rsize);
	set_size_and_pinuse_of_inuse_chunk(ms, p, nb);
      }
      else { /* exhaust dv */
	size_t dvs = ms->dvsize;
	ms->dvsize = 0;
	ms->dv = 0;
	set_inuse_and_pinuse(ms, p, dvs);
      }
      mem = chunk2mem(p);
      check_malloced_chunk(ms, mem, nb);
      goto postaction;
    }

    else if (nb < ms->topsize) { /* Split top */
      size_t rsize = ms->topsize -= nb;
      mchunkptr p = ms->top;
      mchunkptr r = ms->top = chunk_plus_offset(p, nb);
      r->head = rsize | PINUSE_BIT;
      set_size_and_pinuse_of_inuse_chunk(ms, p, nb);
      mem = chunk2mem(p);
      check_top_chunk(ms, ms->top);
      check_malloced_chunk(ms, mem, nb);
      goto postaction;
    }

    mem = sys_alloc(ms, nb);

  postaction:
    POSTACTION(ms);
    return mem;
  }

  return 0;
}
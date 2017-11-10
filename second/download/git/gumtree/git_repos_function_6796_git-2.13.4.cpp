void* dlmalloc(size_t bytes) {
  /*
     Basic algorithm:
     If a small request (< 256 bytes minus per-chunk overhead):
       1. If one exists, use a remainderless chunk in associated smallbin.
	  (Remainderless means that there are too few excess bytes to
	  represent as a chunk.)
       2. If it is big enough, use the dv chunk, which is normally the
	  chunk adjacent to the one used for the most recent small request.
       3. If one exists, split the smallest available chunk in a bin,
	  saving remainder in dv.
       4. If it is big enough, use the top chunk.
       5. If available, get memory from system and use it
     Otherwise, for a large request:
       1. Find the smallest available binned chunk that fits, and use it
	  if it is better fitting than dv chunk, splitting if necessary.
       2. If better fitting than any binned chunk, use the dv chunk.
       3. If it is big enough, use the top chunk.
       4. If request size >= mmap threshold, try to directly mmap this chunk.
       5. If available, get memory from system and use it

     The ugly goto's here ensure that postaction occurs along all paths.
  */

#if USE_LOCKS
  ensure_initialization(); /* initialize in sys_alloc if not using locks */
#endif

  if (!PREACTION(gm)) {
    void* mem;
    size_t nb;
    if (bytes <= MAX_SMALL_REQUEST) {
      bindex_t idx;
      binmap_t smallbits;
      nb = (bytes < MIN_REQUEST)? MIN_CHUNK_SIZE : pad_request(bytes);
      idx = small_index(nb);
      smallbits = gm->smallmap >> idx;

      if ((smallbits & 0x3U) != 0) { /* Remainderless fit to a smallbin. */
	mchunkptr b, p;
	idx += ~smallbits & 1;       /* Uses next bin if idx empty */
	b = smallbin_at(gm, idx);
	p = b->fd;
	assert(chunksize(p) == small_index2size(idx));
	unlink_first_small_chunk(gm, b, p, idx);
	set_inuse_and_pinuse(gm, p, small_index2size(idx));
	mem = chunk2mem(p);
	check_malloced_chunk(gm, mem, nb);
	goto postaction;
      }

      else if (nb > gm->dvsize) {
	if (smallbits != 0) { /* Use chunk in next nonempty smallbin */
	  mchunkptr b, p, r;
	  size_t rsize;
	  bindex_t i;
	  binmap_t leftbits = (smallbits << idx) & left_bits(idx2bit(idx));
	  binmap_t leastbit = least_bit(leftbits);
	  compute_bit2idx(leastbit, i);
	  b = smallbin_at(gm, i);
	  p = b->fd;
	  assert(chunksize(p) == small_index2size(i));
	  unlink_first_small_chunk(gm, b, p, i);
	  rsize = small_index2size(i) - nb;
	  /* Fit here cannot be remainderless if 4byte sizes */
	  if (SIZE_T_SIZE != 4 && rsize < MIN_CHUNK_SIZE)
	    set_inuse_and_pinuse(gm, p, small_index2size(i));
	  else {
	    set_size_and_pinuse_of_inuse_chunk(gm, p, nb);
	    r = chunk_plus_offset(p, nb);
	    set_size_and_pinuse_of_free_chunk(r, rsize);
	    replace_dv(gm, r, rsize);
	  }
	  mem = chunk2mem(p);
	  check_malloced_chunk(gm, mem, nb);
	  goto postaction;
	}

	else if (gm->treemap != 0 && (mem = tmalloc_small(gm, nb)) != 0) {
	  check_malloced_chunk(gm, mem, nb);
	  goto postaction;
	}
      }
    }
    else if (bytes >= MAX_REQUEST)
      nb = MAX_SIZE_T; /* Too big to allocate. Force failure (in sys alloc) */
    else {
      nb = pad_request(bytes);
      if (gm->treemap != 0 && (mem = tmalloc_large(gm, nb)) != 0) {
	check_malloced_chunk(gm, mem, nb);
	goto postaction;
      }
    }

    if (nb <= gm->dvsize) {
      size_t rsize = gm->dvsize - nb;
      mchunkptr p = gm->dv;
      if (rsize >= MIN_CHUNK_SIZE) { /* split dv */
	mchunkptr r = gm->dv = chunk_plus_offset(p, nb);
	gm->dvsize = rsize;
	set_size_and_pinuse_of_free_chunk(r, rsize);
	set_size_and_pinuse_of_inuse_chunk(gm, p, nb);
      }
      else { /* exhaust dv */
	size_t dvs = gm->dvsize;
	gm->dvsize = 0;
	gm->dv = 0;
	set_inuse_and_pinuse(gm, p, dvs);
      }
      mem = chunk2mem(p);
      check_malloced_chunk(gm, mem, nb);
      goto postaction;
    }

    else if (nb < gm->topsize) { /* Split top */
      size_t rsize = gm->topsize -= nb;
      mchunkptr p = gm->top;
      mchunkptr r = gm->top = chunk_plus_offset(p, nb);
      r->head = rsize | PINUSE_BIT;
      set_size_and_pinuse_of_inuse_chunk(gm, p, nb);
      mem = chunk2mem(p);
      check_top_chunk(gm, gm->top);
      check_malloced_chunk(gm, mem, nb);
      goto postaction;
    }

    mem = sys_alloc(gm, nb);

  postaction:
    POSTACTION(gm);
    return mem;
  }

  return 0;
}
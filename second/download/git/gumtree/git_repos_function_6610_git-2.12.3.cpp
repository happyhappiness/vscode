void dlfree(void* mem) {
  /*
     Consolidate freed chunks with preceding or succeeding bordering
     free chunks, if they exist, and then place in a bin.  Intermixed
     with special cases for top, dv, mmapped chunks, and usage errors.
  */

  if (mem != 0) {
    mchunkptr p  = mem2chunk(mem);
#if FOOTERS
    mstate fm = get_mstate_for(p);
    if (!ok_magic(fm)) {
      USAGE_ERROR_ACTION(fm, p);
      return;
    }
#else /* FOOTERS */
#define fm gm
#endif /* FOOTERS */
    if (!PREACTION(fm)) {
      check_inuse_chunk(fm, p);
      if (RTCHECK(ok_address(fm, p) && ok_cinuse(p))) {
	size_t psize = chunksize(p);
	mchunkptr next = chunk_plus_offset(p, psize);
	if (!pinuse(p)) {
	  size_t prevsize = p->prev_foot;
	  if ((prevsize & IS_MMAPPED_BIT) != 0) {
	    prevsize &= ~IS_MMAPPED_BIT;
	    psize += prevsize + MMAP_FOOT_PAD;
	    if (CALL_MUNMAP((char*)p - prevsize, psize) == 0)
	      fm->footprint -= psize;
	    goto postaction;
	  }
	  else {
	    mchunkptr prev = chunk_minus_offset(p, prevsize);
	    psize += prevsize;
	    p = prev;
	    if (RTCHECK(ok_address(fm, prev))) { /* consolidate backward */
	      if (p != fm->dv) {
		unlink_chunk(fm, p, prevsize);
	      }
	      else if ((next->head & INUSE_BITS) == INUSE_BITS) {
		fm->dvsize = psize;
		set_free_with_pinuse(p, psize, next);
		goto postaction;
	      }
	    }
	    else
	      goto erroraction;
	  }
	}

	if (RTCHECK(ok_next(p, next) && ok_pinuse(next))) {
	  if (!cinuse(next)) {  /* consolidate forward */
	    if (next == fm->top) {
	      size_t tsize = fm->topsize += psize;
	      fm->top = p;
	      p->head = tsize | PINUSE_BIT;
	      if (p == fm->dv) {
		fm->dv = 0;
		fm->dvsize = 0;
	      }
	      if (should_trim(fm, tsize))
		sys_trim(fm, 0);
	      goto postaction;
	    }
	    else if (next == fm->dv) {
	      size_t dsize = fm->dvsize += psize;
	      fm->dv = p;
	      set_size_and_pinuse_of_free_chunk(p, dsize);
	      goto postaction;
	    }
	    else {
	      size_t nsize = chunksize(next);
	      psize += nsize;
	      unlink_chunk(fm, next, nsize);
	      set_size_and_pinuse_of_free_chunk(p, psize);
	      if (p == fm->dv) {
		fm->dvsize = psize;
		goto postaction;
	      }
	    }
	  }
	  else
	    set_free_with_pinuse(p, psize, next);

	  if (is_small(psize)) {
	    insert_small_chunk(fm, p, psize);
	    check_free_chunk(fm, p);
	  }
	  else {
	    tchunkptr tp = (tchunkptr)p;
	    insert_large_chunk(fm, tp, psize);
	    check_free_chunk(fm, p);
	    if (--fm->release_checks == 0)
	      release_unused_segments(fm);
	  }
	  goto postaction;
	}
      }
    erroraction:
      USAGE_ERROR_ACTION(fm, p);
    postaction:
      POSTACTION(fm);
    }
  }
#if !FOOTERS
#undef fm
#endif /* FOOTERS */
}
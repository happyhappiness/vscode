static int sys_trim(mstate m, size_t pad) {
  size_t released = 0;
  ensure_initialization();
  if (pad < MAX_REQUEST && is_initialized(m)) {
    pad += TOP_FOOT_SIZE; /* ensure enough room for segment overhead */

    if (m->topsize > pad) {
      /* Shrink top space in granularity-size units, keeping at least one */
      size_t unit = mparams.granularity;
      size_t extra = ((m->topsize - pad + (unit - SIZE_T_ONE)) / unit -
		      SIZE_T_ONE) * unit;
      msegmentptr sp = segment_holding(m, (char*)m->top);

      if (!is_extern_segment(sp)) {
	if (is_mmapped_segment(sp)) {
	  if (HAVE_MMAP &&
	      sp->size >= extra &&
	      !has_segment_link(m, sp)) { /* can't shrink if pinned */
	    size_t newsize = sp->size - extra;
	    /* Prefer mremap, fall back to munmap */
	    if ((CALL_MREMAP(sp->base, sp->size, newsize, 0) != MFAIL) ||
		(CALL_MUNMAP(sp->base + newsize, extra) == 0)) {
	      released = extra;
	    }
	  }
	}
	else if (HAVE_MORECORE) {
	  if (extra >= HALF_MAX_SIZE_T) /* Avoid wrapping negative */
	    extra = (HALF_MAX_SIZE_T) + SIZE_T_ONE - unit;
	  ACQUIRE_MALLOC_GLOBAL_LOCK();
	  {
	    /* Make sure end of memory is where we last set it. */
	    char* old_br = (char*)(CALL_MORECORE(0));
	    if (old_br == sp->base + sp->size) {
	      char* rel_br = (char*)(CALL_MORECORE(-extra));
	      char* new_br = (char*)(CALL_MORECORE(0));
	      if (rel_br != CMFAIL && new_br < old_br)
		released = old_br - new_br;
	    }
	  }
	  RELEASE_MALLOC_GLOBAL_LOCK();
	}
      }

      if (released != 0) {
	sp->size -= released;
	m->footprint -= released;
	init_top(m, m->top, m->topsize - released);
	check_top_chunk(m, m->top);
      }
    }

    /* Unmap any unused mmapped segments */
    if (HAVE_MMAP)
      released += release_unused_segments(m);

    /* On failure, disable autotrim to avoid repeated failed future calls */
    if (released == 0 && m->topsize > m->trim_check)
      m->trim_check = MAX_SIZE_T;
  }

  return (released != 0)? 1 : 0;
}
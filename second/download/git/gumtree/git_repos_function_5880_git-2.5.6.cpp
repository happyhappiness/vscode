static void* sys_alloc(mstate m, size_t nb) {
  char* tbase = CMFAIL;
  size_t tsize = 0;
  flag_t mmap_flag = 0;

  ensure_initialization();

  /* Directly map large chunks */
  if (use_mmap(m) && nb >= mparams.mmap_threshold) {
    void* mem = mmap_alloc(m, nb);
    if (mem != 0)
      return mem;
  }

  /*
    Try getting memory in any of three ways (in most-preferred to
    least-preferred order):
    1. A call to MORECORE that can normally contiguously extend memory.
       (disabled if not MORECORE_CONTIGUOUS or not HAVE_MORECORE or
       main space is mmapped or a previous contiguous call failed)
    2. A call to MMAP new space (disabled if not HAVE_MMAP).
       Note that under the default settings, if MORECORE is unable to
       fulfill a request, and HAVE_MMAP is true, then mmap is
       used as a noncontiguous system allocator. This is a useful backup
       strategy for systems with holes in address spaces -- in this case
       sbrk cannot contiguously expand the heap, but mmap may be able to
       find space.
    3. A call to MORECORE that cannot usually contiguously extend memory.
       (disabled if not HAVE_MORECORE)

   In all cases, we need to request enough bytes from system to ensure
   we can malloc nb bytes upon success, so pad with enough space for
   top_foot, plus alignment-pad to make sure we don't lose bytes if
   not on boundary, and round this up to a granularity unit.
  */

  if (MORECORE_CONTIGUOUS && !use_noncontiguous(m)) {
    char* br = CMFAIL;
    msegmentptr ss = (m->top == 0)? 0 : segment_holding(m, (char*)m->top);
    size_t asize = 0;
    ACQUIRE_MALLOC_GLOBAL_LOCK();

    if (ss == 0) {  /* First time through or recovery */
      char* base = (char*)CALL_MORECORE(0);
      if (base != CMFAIL) {
	asize = granularity_align(nb + SYS_ALLOC_PADDING);
	/* Adjust to end on a page boundary */
	if (!is_page_aligned(base))
	  asize += (page_align((size_t)base) - (size_t)base);
	/* Can't call MORECORE if size is negative when treated as signed */
	if (asize < HALF_MAX_SIZE_T &&
	    (br = (char*)(CALL_MORECORE(asize))) == base) {
	  tbase = base;
	  tsize = asize;
	}
      }
    }
    else {
      /* Subtract out existing available top space from MORECORE request. */
      asize = granularity_align(nb - m->topsize + SYS_ALLOC_PADDING);
      /* Use mem here only if it did continuously extend old space */
      if (asize < HALF_MAX_SIZE_T &&
	  (br = (char*)(CALL_MORECORE(asize))) == ss->base+ss->size) {
	tbase = br;
	tsize = asize;
      }
    }

    if (tbase == CMFAIL) {    /* Cope with partial failure */
      if (br != CMFAIL) {    /* Try to use/extend the space we did get */
	if (asize < HALF_MAX_SIZE_T &&
	    asize < nb + SYS_ALLOC_PADDING) {
	  size_t esize = granularity_align(nb + SYS_ALLOC_PADDING - asize);
	  if (esize < HALF_MAX_SIZE_T) {
	    char* end = (char*)CALL_MORECORE(esize);
	    if (end != CMFAIL)
	      asize += esize;
	    else {            /* Can't use; try to release */
	      (void) CALL_MORECORE(-asize);
	      br = CMFAIL;
	    }
	  }
	}
      }
      if (br != CMFAIL) {    /* Use the space we did get */
	tbase = br;
	tsize = asize;
      }
      else
	disable_contiguous(m); /* Don't try contiguous path in the future */
    }

    RELEASE_MALLOC_GLOBAL_LOCK();
  }

  if (HAVE_MMAP && tbase == CMFAIL) {  /* Try MMAP */
    size_t rsize = granularity_align(nb + SYS_ALLOC_PADDING);
    if (rsize > nb) { /* Fail if wraps around zero */
      char* mp = (char*)(CALL_MMAP(rsize));
      if (mp != CMFAIL) {
	tbase = mp;
	tsize = rsize;
	mmap_flag = IS_MMAPPED_BIT;
      }
    }
  }

  if (HAVE_MORECORE && tbase == CMFAIL) { /* Try noncontiguous MORECORE */
    size_t asize = granularity_align(nb + SYS_ALLOC_PADDING);
    if (asize < HALF_MAX_SIZE_T) {
      char* br = CMFAIL;
      char* end = CMFAIL;
      ACQUIRE_MALLOC_GLOBAL_LOCK();
      br = (char*)(CALL_MORECORE(asize));
      end = (char*)(CALL_MORECORE(0));
      RELEASE_MALLOC_GLOBAL_LOCK();
      if (br != CMFAIL && end != CMFAIL && br < end) {
	size_t ssize = end - br;
	if (ssize > nb + TOP_FOOT_SIZE) {
	  tbase = br;
	  tsize = ssize;
	}
      }
    }
  }

  if (tbase != CMFAIL) {

    if ((m->footprint += tsize) > m->max_footprint)
      m->max_footprint = m->footprint;

    if (!is_initialized(m)) { /* first-time initialization */
      m->seg.base = m->least_addr = tbase;
      m->seg.size = tsize;
      m->seg.sflags = mmap_flag;
      m->magic = mparams.magic;
      m->release_checks = MAX_RELEASE_CHECK_RATE;
      init_bins(m);
#if !ONLY_MSPACES
      if (is_global(m))
	init_top(m, (mchunkptr)tbase, tsize - TOP_FOOT_SIZE);
      else
#endif
      {
	/* Offset top by embedded malloc_state */
	mchunkptr mn = next_chunk(mem2chunk(m));
	init_top(m, mn, (size_t)((tbase + tsize) - (char*)mn) -TOP_FOOT_SIZE);
      }
    }

    else {
      /* Try to merge with an existing segment */
      msegmentptr sp = &m->seg;
      /* Only consider most recent segment if traversal suppressed */
      while (sp != 0 && tbase != sp->base + sp->size)
	sp = (NO_SEGMENT_TRAVERSAL) ? 0 : sp->next;
      if (sp != 0 &&
	  !is_extern_segment(sp) &&
	  (sp->sflags & IS_MMAPPED_BIT) == mmap_flag &&
	  segment_holds(sp, m->top)) { /* append */
	sp->size += tsize;
	init_top(m, m->top, m->topsize + tsize);
      }
      else {
	if (tbase < m->least_addr)
	  m->least_addr = tbase;
	sp = &m->seg;
	while (sp != 0 && sp->base != tbase + tsize)
	  sp = (NO_SEGMENT_TRAVERSAL) ? 0 : sp->next;
	if (sp != 0 &&
	    !is_extern_segment(sp) &&
	    (sp->sflags & IS_MMAPPED_BIT) == mmap_flag) {
	  char* oldbase = sp->base;
	  sp->base = tbase;
	  sp->size += tsize;
	  return prepend_alloc(m, tbase, oldbase, nb);
	}
	else
	  add_segment(m, tbase, tsize, mmap_flag);
      }
    }

    if (nb < m->topsize) { /* Allocate from new or extended top space */
      size_t rsize = m->topsize -= nb;
      mchunkptr p = m->top;
      mchunkptr r = m->top = chunk_plus_offset(p, nb);
      r->head = rsize | PINUSE_BIT;
      set_size_and_pinuse_of_inuse_chunk(m, p, nb);
      check_top_chunk(m, m->top);
      check_malloced_chunk(m, chunk2mem(p), nb);
      return chunk2mem(p);
    }
  }

  MALLOC_FAILURE_ACTION;
  return 0;
}
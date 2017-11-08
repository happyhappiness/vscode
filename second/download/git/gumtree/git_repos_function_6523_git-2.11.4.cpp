static size_t release_unused_segments(mstate m) {
  size_t released = 0;
  int nsegs = 0;
  msegmentptr pred = &m->seg;
  msegmentptr sp = pred->next;
  while (sp != 0) {
    char* base = sp->base;
    size_t size = sp->size;
    msegmentptr next = sp->next;
    ++nsegs;
    if (is_mmapped_segment(sp) && !is_extern_segment(sp)) {
      mchunkptr p = align_as_chunk(base);
      size_t psize = chunksize(p);
      /* Can unmap if first chunk holds entire segment and not pinned */
      if (!cinuse(p) && (char*)p + psize >= base + size - TOP_FOOT_SIZE) {
	tchunkptr tp = (tchunkptr)p;
	assert(segment_holds(sp, (char*)sp));
	if (p == m->dv) {
	  m->dv = 0;
	  m->dvsize = 0;
	}
	else {
	  unlink_large_chunk(m, tp);
	}
	if (CALL_MUNMAP(base, size) == 0) {
	  released += size;
	  m->footprint -= size;
	  /* unlink obsoleted record */
	  sp = pred;
	  sp->next = next;
	}
	else { /* back out if cannot unmap */
	  insert_large_chunk(m, tp, psize);
	}
      }
    }
    if (NO_SEGMENT_TRAVERSAL) /* scan only first segment */
      break;
    pred = sp;
    sp = next;
  }
  /* Reset check counter */
  m->release_checks = ((nsegs > MAX_RELEASE_CHECK_RATE)?
		       nsegs : MAX_RELEASE_CHECK_RATE);
  return released;
}
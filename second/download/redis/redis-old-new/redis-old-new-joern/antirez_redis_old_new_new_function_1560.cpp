void *
huge_ralloc(void *ptr, size_t oldsize, size_t size, size_t extra,
    size_t alignment, bool zero, bool try_tcache_dalloc, dss_prec_t dss_prec)
{
	void *ret;
	size_t copysize;

	/* Try to avoid moving the allocation. */
	if (huge_ralloc_no_move(ptr, oldsize, size, extra) == false)
		return (ptr);

	/*
	 * size and oldsize are different enough that we need to use a
	 * different size class.  In that case, fall back to allocating new
	 * space and copying.
	 */
	if (alignment > chunksize)
		ret = huge_palloc(size + extra, alignment, zero, dss_prec);
	else
		ret = huge_malloc(size + extra, zero, dss_prec);

	if (ret == NULL) {
		if (extra == 0)
			return (NULL);
		/* Try again, this time without extra. */
		if (alignment > chunksize)
			ret = huge_palloc(size, alignment, zero, dss_prec);
		else
			ret = huge_malloc(size, zero, dss_prec);

		if (ret == NULL)
			return (NULL);
	}

	/*
	 * Copy at most size bytes (not size+extra), since the caller has no
	 * expectation that the extra bytes will be reliably preserved.
	 */
	copysize = (size < oldsize) ? size : oldsize;

#ifdef JEMALLOC_MREMAP
	/*
	 * Use mremap(2) if this is a huge-->huge reallocation, and neither the
	 * source nor the destination are in dss.
	 */
	if (oldsize >= chunksize && (config_dss == false || (chunk_in_dss(ptr)
	    == false && chunk_in_dss(ret) == false))) {
		size_t newsize = huge_salloc(ret);

		/*
		 * Remove ptr from the tree of huge allocations before
		 * performing the remap operation, in order to avoid the
		 * possibility of another thread acquiring that mapping before
		 * this one removes it from the tree.
		 */
		huge_dalloc(ptr, false);
		if (mremap(ptr, oldsize, newsize, MREMAP_MAYMOVE|MREMAP_FIXED,
		    ret) == MAP_FAILED) {
			/*
			 * Assuming no chunk management bugs in the allocator,
			 * the only documented way an error can occur here is
			 * if the application changed the map type for a
			 * portion of the old allocation.  This is firmly in
			 * undefined behavior territory, so write a diagnostic
			 * message, and optionally abort.
			 */
			char buf[BUFERROR_BUF];

			buferror(get_errno(), buf, sizeof(buf));
			malloc_printf("<jemalloc>: Error in mremap(): %s\n",
			    buf);
			if (opt_abort)
				abort();
			memcpy(ret, ptr, copysize);
			chunk_dealloc_mmap(ptr, oldsize);
		} else if (config_fill && zero == false && opt_junk && oldsize
		    < newsize) {
			/*
			 * mremap(2) clobbers the original mapping, so
			 * junk/zero filling is not preserved.  There is no
			 * need to zero fill here, since any trailing
			 * uninititialized memory is demand-zeroed by the
			 * kernel, but junk filling must be redone.
			 */
			memset(ret + oldsize, 0xa5, newsize - oldsize);
		}
	} else
#endif
	{
		memcpy(ret, ptr, copysize);
		iqalloct(ptr, try_tcache_dalloc);
	}
	return (ret);
}
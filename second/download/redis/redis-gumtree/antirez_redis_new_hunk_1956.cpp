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

#ifdef JEMALLOC_JET
#undef huge_dalloc_junk
#define	huge_dalloc_junk JEMALLOC_N(huge_dalloc_junk_impl)
#endif
static void
huge_dalloc_junk(void *ptr, size_t usize)
{

	if (config_fill && config_dss && opt_junk) {
		/*
		 * Only bother junk filling if the chunk isn't about to be
		 * unmapped.
		 */
		if (config_munmap == false || (config_dss && chunk_in_dss(ptr)))
			memset(ptr, 0x5a, usize);
	}
}
#ifdef JEMALLOC_JET
#undef huge_dalloc_junk
#define	huge_dalloc_junk JEMALLOC_N(huge_dalloc_junk)
huge_dalloc_junk_t *huge_dalloc_junk = JEMALLOC_N(huge_dalloc_junk_impl);
#endif

void
huge_dalloc(void *ptr, bool unmap)
{

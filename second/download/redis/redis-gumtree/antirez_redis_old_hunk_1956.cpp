			 */
			char buf[BUFERROR_BUF];

			buferror(buf, sizeof(buf));
			malloc_printf("<jemalloc>: Error in mremap(): %s\n",
			    buf);
			if (opt_abort)
				abort();
			memcpy(ret, ptr, copysize);
			chunk_dealloc_mmap(ptr, oldsize);
		}
	} else
#endif
	{
		memcpy(ret, ptr, copysize);
		iqallocx(ptr, try_tcache_dalloc);
	}
	return (ret);
}

void
huge_dalloc(void *ptr, bool unmap)
{

malloc_printf("<jemalloc>: Leak summary: %"PRId64" byte%s, %"
		    PRId64" object%s, %zu context%s\n",
		    cnt_all->curbytes, (cnt_all->curbytes != 1) ? "s" : "",
		    cnt_all->curobjs, (cnt_all->curobjs != 1) ? "s" : "",
		    leak_nctx, (leak_nctx != 1) ? "s" : "");
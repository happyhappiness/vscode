(prof_dump_printf(propagate_err,
		    "heap profile: %"PRId64": %"PRId64
		    " [%"PRIu64": %"PRIu64"] @ heap_v2/%"PRIu64"\n",
		    cnt_all->curobjs, cnt_all->curbytes,
		    cnt_all->accumobjs, cnt_all->accumbytes,
		    ((uint64_t)1U << opt_lg_prof_sample));
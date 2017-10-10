 	default:
 		return error("unknown file mode for %s in index", path);
 	}
 
 finish:
 	if (state->refresh_cache) {
+		assert(state->istate);
 		if (!fstat_done)
 			lstat(ce->name, &st);
 		fill_stat_cache_info(ce, &st);
+		ce->ce_flags |= CE_UPDATE_IN_BASE;
+		state->istate->cache_changed |= CE_ENTRY_CHANGED;
 	}
 	return 0;
 }
 
 /*
  * This is like 'lstat()', except it refuses to follow symlinks

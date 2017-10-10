			if (patch->is_new < 0)
				goto is_new;
			return error(_("%s: does not exist in index"), old_name);
		}
		*ce = active_cache[pos];
		if (stat_ret < 0) {
			if (checkout_target(*ce, st))
				return -1;
		}
		if (!cached && verify_index_match(*ce, st))
			return error(_("%s: does not match index"), old_name);
		if (cached)
			st_mode = (*ce)->ce_mode;

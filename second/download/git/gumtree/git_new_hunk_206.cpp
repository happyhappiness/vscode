				return error(_("Could not parse object '%s'"),
					sha1_to_hex(base_list[i]));
			commit_list_insert(base, &ca);
		}
	}

	hold_locked_index(lock, 1);
	clean = merge_recursive(o, head_commit, next_commit, ca,
			result);
	if (active_cache_changed &&
	    write_locked_index(&the_index, lock, COMMIT_LOCK))
		return error(_("Unable to write index."));

	return clean ? 0 : 1;
}

static int merge_recursive_config(const char *var, const char *value, void *cb)

((parsed_kws & MTREE_HAS_SIZE) == 0 ||
			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
				archive_entry_set_size(entry, st->st_size)
(mtree->set.processing &&
		    (mtree->set.keys & F_FLAGS) != 0)
			/* Overwrite the global parameter. */
			archive_strcat(str, " flags=none")
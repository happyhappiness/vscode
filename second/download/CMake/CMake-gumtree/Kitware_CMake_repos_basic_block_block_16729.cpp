(archive_strlen(&me->fflags_text) > 0) {
			archive_strcat(str, " flags=");
			mtree_quote(str, me->fflags_text.s);
		} else if (mtree->set.processing &&
		    (mtree->set.keys & F_FLAGS) != 0)
			/* Overwrite the global parameter. */
			archive_strcat(str, " flags=none")
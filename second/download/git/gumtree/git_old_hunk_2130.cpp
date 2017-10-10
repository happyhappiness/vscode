			else if (options->single_follow &&
				 strcmp(options->single_follow, p->two->path))
				continue; /* not interested */
			else if (!DIFF_OPT_TST(options, RENAME_EMPTY) &&
				 is_empty_blob_sha1(p->two->sha1))
				continue;
			else
				locate_rename_dst(p->two, 1);
		}
		else if (!DIFF_OPT_TST(options, RENAME_EMPTY) &&
			 is_empty_blob_sha1(p->one->sha1))
			continue;
		else if (!DIFF_PAIR_UNMERGED(p) && !DIFF_FILE_VALID(p->two)) {
			/*

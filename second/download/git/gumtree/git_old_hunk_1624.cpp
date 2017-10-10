		for (i = 0; i < refspec_nr; i++) {
			struct refspec *rs = refspec + i;

			if (rs->pattern || rs->matching)
				continue;

			/*
			 * LHS must match a single ref
			 * NEEDSWORK: add logic to special case 'HEAD' once
			 * working with submodules in a detached head state
			 * ceases to be the norm.
			 */
			if (count_refspec_match(rs->src, local_refs, NULL) != 1)
				die("src refspec '%s' must name a ref",
				    rs->src);
		}
		free_refspec(refspec_nr, refspec);
	}

	return 0;
}

static int absorb_git_dirs(int argc, const char **argv, const char *prefix)
{

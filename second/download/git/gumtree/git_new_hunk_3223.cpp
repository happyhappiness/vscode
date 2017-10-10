				die("unordered stage entries for '%s'",
				    ce->name);
		}
	}
}

static void tweak_untracked_cache(struct index_state *istate)
{
	switch (git_config_get_untracked_cache()) {
	case -1: /* keep: do nothing */
		break;
	case 0: /* false */
		remove_untracked_cache(istate);
		break;
	case 1: /* true */
		add_untracked_cache(istate);
		break;
	default: /* unknown value: do nothing */
		break;
	}
}

static void post_read_index_from(struct index_state *istate)
{
	check_ce_order(istate);
	tweak_untracked_cache(istate);
}

/* remember to discard_cache() before reading a different cache! */
int do_read_index(struct index_state *istate, const char *path, int must_exist)
{
	int fd, i;
	struct stat st;
	unsigned long src_offset;

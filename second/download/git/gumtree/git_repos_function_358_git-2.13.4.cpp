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
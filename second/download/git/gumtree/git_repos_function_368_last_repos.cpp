static void tweak_split_index(struct index_state *istate)
{
	switch (git_config_get_split_index()) {
	case -1: /* unset: do nothing */
		break;
	case 0: /* false */
		remove_split_index(istate);
		break;
	case 1: /* true */
		add_split_index(istate);
		break;
	default: /* unknown value: do nothing */
		break;
	}
}
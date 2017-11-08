static int match_stat_with_submodule(struct diff_options *diffopt,
				     const struct cache_entry *ce,
				     struct stat *st, unsigned ce_option,
				     unsigned *dirty_submodule)
{
	int changed = ce_match_stat(ce, st, ce_option);
	if (S_ISGITLINK(ce->ce_mode)) {
		unsigned orig_flags = diffopt->flags;
		if (!DIFF_OPT_TST(diffopt, OVERRIDE_SUBMODULE_CONFIG))
			set_diffopt_flags_from_submodule_config(diffopt, ce->name);
		if (DIFF_OPT_TST(diffopt, IGNORE_SUBMODULES))
			changed = 0;
		else if (!DIFF_OPT_TST(diffopt, IGNORE_DIRTY_SUBMODULES)
		    && (!changed || DIFF_OPT_TST(diffopt, DIRTY_SUBMODULES)))
			*dirty_submodule = is_submodule_modified(ce->name, DIFF_OPT_TST(diffopt, IGNORE_UNTRACKED_IN_SUBMODULES));
		diffopt->flags = orig_flags;
	}
	return changed;
}
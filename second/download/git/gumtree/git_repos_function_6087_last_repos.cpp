static void die_if_unmerged_cache(int reset_type)
{
	if (is_merge() || unmerged_cache())
		die(_("Cannot do a %s reset in the middle of a merge."),
		    _(reset_type_names[reset_type]));

}
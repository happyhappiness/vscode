void NORETURN die_conclude_merge(void)
{
	error(_("You have not concluded your merge (MERGE_HEAD exists)."));
	if (advice_resolve_conflict)
		advise(_("Please, commit your changes before you can merge."));
	die(_("Exiting because of unfinished merge."));
}
void NORETURN die_resolve_conflict(const char *me)
{
	error_resolve_conflict(me);
	die("Exiting because of an unresolved conflict.");
}

void NORETURN die_conclude_merge(void)
{
	error(_("You have not concluded your merge (MERGE_HEAD exists)."));
	if (advice_resolve_conflict)
		advise(_("Please, commit your changes before you can merge."));
	die(_("Exiting because of unfinished merge."));
}

void detach_advice(const char *new_name)
{
	const char fmt[] =
	"Note: checking out '%s'.\n\n"
	"You are in 'detached HEAD' state. You can look around, make experimental\n"
	"changes and commit them, and you can discard any commits you make in this\n"

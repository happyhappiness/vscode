void NORETURN die_resolve_conflict(const char *me)
{
	error_resolve_conflict(me);
	die("Exiting because of an unresolved conflict.");
}

void detach_advice(const char *new_name)
{
	const char fmt[] =
	"Note: checking out '%s'.\n\n"
	"You are in 'detached HEAD' state. You can look around, make experimental\n"
	"changes and commit them, and you can discard any commits you make in this\n"

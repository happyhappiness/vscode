void NORETURN die_resolve_conflict(const char *me)
{
	error_resolve_conflict(me);
	die("Exiting because of an unresolved conflict.");
}
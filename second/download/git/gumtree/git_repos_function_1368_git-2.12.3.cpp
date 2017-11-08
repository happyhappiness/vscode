static NORETURN void die_want_option(const char *option_name)
{
	die(_("option '%s' requires a value"), option_name);
}
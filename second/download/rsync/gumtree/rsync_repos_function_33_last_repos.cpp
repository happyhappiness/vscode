static void reset_all_vars(void)
{
	memcpy(&Vars, &Defaults, sizeof Vars);
}
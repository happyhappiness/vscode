static void init_section(local_vars *psection)
{
	memset(psection, 0, sizeof (local_vars));
	copy_section(psection, &Vars.l);
}
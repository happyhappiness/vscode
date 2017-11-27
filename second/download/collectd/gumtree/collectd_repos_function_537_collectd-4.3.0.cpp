static void rra_free (int rra_num, char **rra_def)
{
	int i;

	for (i = 0; i < rra_num; i++)
	{
		sfree (rra_def[i]);
	}
	sfree (rra_def);
}
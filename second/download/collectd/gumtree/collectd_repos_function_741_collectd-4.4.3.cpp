static void free_sockent (sockent_t *se)
{
	sockent_t *next;
	while (se != NULL)
	{
		next = se->next;
		free (se->addr);
		free (se);
		se = next;
	}
}
static void prepare_packed_git_mru(void)
{
	struct packed_git *p;

	mru_clear(packed_git_mru);
	for (p = packed_git; p; p = p->next)
		mru_append(packed_git_mru, p);
}
static void load_all(void)
{
	struct packed_git *p = packed_git;

	while (p) {
		add_pack(p);
		p = p->next;
	}
}
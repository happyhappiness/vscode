static void pll_free(struct pll *l)
{
	struct pll *old;
	struct pack_list *opl;

	while (l) {
		old = l;
		while (l->pl) {
			opl = l->pl;
			l->pl = opl->next;
			free(opl);
		}
		l = l->next;
		free(old);
	}
}
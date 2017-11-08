static int name_first_parent_chain(struct commit *c)
{
	int i = 0;
	while (c) {
		struct commit *p;
		if (!c->util)
			break;
		if (!c->parents)
			break;
		p = c->parents->item;
		if (!p->util) {
			name_parent(c, p);
			i++;
		}
		else
			break;
		c = p;
	}
	return i;
}
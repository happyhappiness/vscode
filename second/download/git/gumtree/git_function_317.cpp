static void show_mode_change(struct patch *p, int show_name)
{
	if (p->old_mode && p->new_mode && p->old_mode != p->new_mode) {
		if (show_name)
			printf(" mode change %06o => %06o %s\n",
			       p->old_mode, p->new_mode, p->new_name);
		else
			printf(" mode change %06o => %06o\n",
			       p->old_mode, p->new_mode);
	}
}
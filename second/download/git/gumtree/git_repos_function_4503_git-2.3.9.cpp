static int calc_maxwidth(struct ref_list *refs)
{
	int i, w = 0;
	for (i = 0; i < refs->index; i++) {
		if (refs->list[i].ignore)
			continue;
		if (refs->list[i].width > w)
			w = refs->list[i].width;
	}
	return w;
}
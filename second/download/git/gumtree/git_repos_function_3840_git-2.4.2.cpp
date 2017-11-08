static int lines_contain_alnum(xdfenv_t *xe, int i, int chg)
{
	for (; chg; chg--, i++)
		if (line_contains_alnum(xe->xdf2.recs[i]->ptr,
				xe->xdf2.recs[i]->size))
			return 1;
	return 0;
}
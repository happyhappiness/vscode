static int levenshtein_compare(const void *p1, const void *p2)
{
	const struct cmdname *const *c1 = p1, *const *c2 = p2;
	const char *s1 = (*c1)->name, *s2 = (*c2)->name;
	int l1 = (*c1)->len;
	int l2 = (*c2)->len;
	return l1 != l2 ? l1 - l2 : strcmp(s1, s2);
}
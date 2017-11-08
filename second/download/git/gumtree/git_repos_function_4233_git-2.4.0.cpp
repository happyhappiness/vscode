static int compare_refs(const void *a_, const void *b_)
{
	struct refinfo *a = *((struct refinfo **)a_);
	struct refinfo *b = *((struct refinfo **)b_);
	struct ref_sort *s;

	for (s = ref_sort; s; s = s->next) {
		int cmp = cmp_ref_sort(s, a, b);
		if (cmp)
			return cmp;
	}
	return 0;
}
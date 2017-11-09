static void show_parent_lno(struct sline *sline, unsigned long l0, unsigned long l1, int n, unsigned long null_context)
{
	l0 = sline[l0].p_lno[n];
	l1 = sline[l1].p_lno[n];
	printf(" -%lu,%lu", l0, l1-l0-null_context);
}
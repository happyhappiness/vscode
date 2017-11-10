static void sort_ref_range(int bottom, int top)
{
	qsort(ref_name + bottom, top - bottom, sizeof(ref_name[0]),
	      compare_ref_name);
}
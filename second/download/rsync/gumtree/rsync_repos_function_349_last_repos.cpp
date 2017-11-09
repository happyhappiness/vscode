static int hlink_compare_gnum(int *int1, int *int2)
{
	struct file_struct *f1 = hlink_flist->sorted[*int1];
	struct file_struct *f2 = hlink_flist->sorted[*int2];
	int32 gnum1 = F_HL_GNUM(f1);
	int32 gnum2 = F_HL_GNUM(f2);

	if (gnum1 != gnum2)
		return gnum1 > gnum2 ? 1 : -1;

	return *int1 > *int2 ? 1 : -1;
}
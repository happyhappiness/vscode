static void fsort(struct file_struct **fp, size_t num)
{
	if (num <= 1)
		return;

	if (use_qsort)
		qsort(fp, num, PTR_SIZE, file_compare);
	else {
		struct file_struct **tmp = new_array(struct file_struct *,
						     (num+1) / 2);
		fsort_tmp(fp, num, tmp);
		free(tmp);
	}
}
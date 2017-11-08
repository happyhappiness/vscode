static void fsort_tmp(struct file_struct **fp, size_t num,
		      struct file_struct **tmp)
{
	struct file_struct **f1, **f2, **t;
	size_t n1, n2;

	n1 = num / 2;
	n2 = num - n1;
	f1 = fp;
	f2 = fp + n1;

	if (n1 > 1)
		fsort_tmp(f1, n1, tmp);
	if (n2 > 1)
		fsort_tmp(f2, n2, tmp);

	while (f_name_cmp(*f1, *f2) <= 0) {
		if (!--n1)
			return;
		f1++;
	}

	t = tmp;
	memcpy(t, f1, n1 * PTR_SIZE);

	*f1++ = *f2++, n2--;

	while (n1 > 0 && n2 > 0) {
		if (f_name_cmp(*t, *f2) <= 0)
			*f1++ = *t++, n1--;
		else
			*f1++ = *f2++, n2--;
	}

	if (n1 > 0)
		memcpy(f1, t, n1 * PTR_SIZE);
}
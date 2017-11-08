int f_name_cmp(struct file_struct *f1, struct file_struct *f2)
{
	int dif;
	const uchar *c1, *c2;
	enum fnc_state state1, state2;

	if (!f1 || !f1->basename) {
		if (!f2 || !f2->basename)
			return 0;
		return -1;
	}
	if (!f2 || !f2->basename)
		return 1;

	if (!(c1 = (uchar*)f1->dirname)) {
		state1 = fnc_BASE;
		c1 = (uchar*)f1->basename;
	} else if (!*c1) {
		state1 = fnc_SLASH;
		c1 = (uchar*)"/";
	} else
		state1 = fnc_DIR;
	if (!(c2 = (uchar*)f2->dirname)) {
		state2 = fnc_BASE;
		c2 = (uchar*)f2->basename;
	} else if (!*c2) {
		state2 = fnc_SLASH;
		c2 = (uchar*)"/";
	} else
		state2 = fnc_DIR;

	while (1) {
		if ((dif = (int)*c1 - (int)*c2) != 0)
			break;
		if (!*++c1) {
			switch (state1) {
			case fnc_DIR:
				state1 = fnc_SLASH;
				c1 = (uchar*)"/";
				break;
			case fnc_SLASH:
				state1 = fnc_BASE;
				c1 = (uchar*)f1->basename;
				break;
			case fnc_BASE:
				break;
			}
		}
		if (!*++c2) {
			switch (state2) {
			case fnc_DIR:
				state2 = fnc_SLASH;
				c2 = (uchar*)"/";
				break;
			case fnc_SLASH:
				state2 = fnc_BASE;
				c2 = (uchar*)f2->basename;
				break;
			case fnc_BASE:
				if (!*c1)
					return 0;
				break;
			}
		}
	}

	return dif;
}
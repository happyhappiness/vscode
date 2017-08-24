{
		allow_ldots = 0;
		allow_multidot = 0;
		allow_period = 1;
		allow_vernum = iso9660->opt.allow_vernum;
		if (iso9660->opt.iso_level == 1) {
			fnmax = 8;
			ffmax = 12;/* fnmax + '.' + 3 */
			dnmax = 8;
		} else {
			fnmax = 30;
			ffmax = 31;
			dnmax = 31;
		}
	}
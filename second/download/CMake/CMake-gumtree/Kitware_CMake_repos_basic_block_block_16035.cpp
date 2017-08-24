{
		/*
		 *   "NM" Format:
		 *     e.g. a basename is 'foo'
		 *               len  ver  flg
		 *    +----+----+----+----+----+----+----+----+
		 *    | 'N'| 'M'| 08 | 01 | 00 | 'f'| 'o'| 'o'|
		 *    +----+----+----+----+----+----+----+----+
		 *    <----------------- len ----------------->
		 */
		size_t nmlen = file->basename.length;
		const char *nm = file->basename.s;
		size_t nmmax;

		if (extra_space(&ctl) < 6)
			bp = extra_next_record(&ctl, 6);
		if (bp != NULL) {
			bp[1] = 'N';
			bp[2] = 'M';
			bp[4] = 1;	    /* version	*/
		}
		nmmax = extra_space(&ctl);
		if (nmmax > 0xff)
			nmmax = 0xff;
		while (nmlen + 5 > nmmax) {
			length = (int)nmmax;
			if (bp != NULL) {
				bp[3] = length;
				bp[5] = 0x01;/* Alternate Name continues
					       * in next "NM" field */
				memcpy(bp+6, nm, length - 5);
				bp += length;
			}
			nmlen -= length - 5;
			nm += length - 5;
			extra_tell_used_size(&ctl, length);
			if (extra_space(&ctl) < 6) {
				bp = extra_next_record(&ctl, 6);
				nmmax = extra_space(&ctl);
				if (nmmax > 0xff)
					nmmax = 0xff;
			}
			if (bp != NULL) {
				bp[1] = 'N';
				bp[2] = 'M';
				bp[4] = 1;    /* version */
			}
		}
		length = 5 + (int)nmlen;
		if (bp != NULL) {
			bp[3] = length;
			bp[5] = 0;
			memcpy(bp+6, nm, nmlen);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}
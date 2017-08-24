{
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
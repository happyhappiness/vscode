{
		/*
		 *   "CL" Format:
		 *               len  ver
		 *    +----+----+----+----+------------+
		 *    | 'C'| 'L'| 0C | 01 | *LOCATION  |
		 *    +----+----+----+----+------------+
		 *    0    1    2    3    4           12
		 *    *LOCATION: location of child directory
		 */
		length = 12;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			bp[1] = 'C';
			bp[2] = 'L';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			set_num_733(bp + 5,
			    isoent->rr_child->dir_location);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}
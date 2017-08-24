{
			bp[1] = 'P';
			bp[2] = 'L';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			set_num_733(bp + 5,
			    rr_parent->dir_location);
			bp += length;
		}
{
			bp[1] = 'C';
			bp[2] = 'L';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			set_num_733(bp + 5,
			    isoent->rr_child->dir_location);
			bp += length;
		}
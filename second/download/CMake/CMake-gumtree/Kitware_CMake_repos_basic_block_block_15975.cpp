{
			uint64_t dev;

			bp[1] = 'P';
			bp[2] = 'N';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			dev = (uint64_t)archive_entry_rdev(file->entry);
			set_num_733(bp + 5, (uint32_t)(dev >> 32));
			set_num_733(bp + 13, (uint32_t)(dev & 0xFFFFFFFF));
			bp += length;
		}
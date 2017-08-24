(bp != NULL) {
			bp[1] = 'Z';
			bp[2] = 'F';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			bp[5] = 'p';
			bp[6] = 'z';
			bp[7] = file->zisofs.header_size;
			bp[8] = file->zisofs.log2_bs;
			set_num_733(bp + 9, file->zisofs.uncompressed_size);
			bp += length;
		}
		int r1;
		if (sparse_files) {
			int len1 = MIN(len, SPARSE_WRITE_SIZE);
			r1 = write_sparse(f, buf, len1);
		} else {
			if (!wf_writeBuf) {
				wf_writeBufSize = MAX_MAP_SIZE;
				wf_writeBufCnt  = 0;
				wf_writeBuf = new_array(char, MAX_MAP_SIZE);
				if (!wf_writeBuf)
					out_of_memory("write_file");
			}
			r1 = MIN(len, wf_writeBufSize - wf_writeBufCnt);
			if (r1) {
				memcpy(wf_writeBuf + wf_writeBufCnt, buf, r1);

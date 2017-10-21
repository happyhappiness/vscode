				wf_writeBufSize = WRITE_SIZE * 8;
				wf_writeBufCnt  = 0;
				wf_writeBuf = new_array(char, wf_writeBufSize);
				if (!wf_writeBuf)
					out_of_memory("write_file");
			}
			r1 = MIN(len, wf_writeBufSize - wf_writeBufCnt);
			if (r1) {
				memcpy(wf_writeBuf + wf_writeBufCnt, buf, r1);
				wf_writeBufCnt += r1;
			}
			if (wf_writeBufCnt == wf_writeBufSize) {
				if (flush_write_file(f) < 0)

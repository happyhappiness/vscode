static int receive_data(int f_in,struct map_struct *buf,int fd,char *fname,
			OFF_T total_size)
{
	int i;
	struct sum_struct sum;
	unsigned int len;
	OFF_T offset = 0;
	OFF_T offset2;
	char *data;
	static char file_sum1[MD4_SUM_LENGTH];
	static char file_sum2[MD4_SUM_LENGTH];
	char *map=NULL;

	read_sum_head(f_in, &sum);

	sum_init();

	for (i=recv_token(f_in,&data); i != 0; i=recv_token(f_in,&data)) {
		if (do_progress)
			show_progress(offset, total_size);

		if (i > 0) {
			extern int cleanup_got_literal;

			if (verbose > 3) {
				rprintf(FINFO,"data recv %d at %.0f\n",
					i,(double)offset);
			}

			stats.literal_data += i;
			cleanup_got_literal = 1;

			sum_update(data,i);

			if (fd != -1 && write_file(fd,data,i) != i) {
				rprintf(FERROR, "write failed on %s: %s\n",
					full_fname(fname), strerror(errno));
				exit_cleanup(RERR_FILEIO);
			}
			offset += i;
			continue;
		}

		i = -(i+1);
		offset2 = i*(OFF_T)sum.blength;
		len = sum.blength;
		if (i == (int) sum.count-1 && sum.remainder != 0)
			len = sum.remainder;

		stats.matched_data += len;

		if (verbose > 3)
			rprintf(FINFO,"chunk[%d] of size %d at %.0f offset=%.0f\n",
				i,len,(double)offset2,(double)offset);

		if (buf) {
			map = map_ptr(buf,offset2,len);

			see_token(map, len);
			sum_update(map,len);
		}

		if (fd != -1 && write_file(fd,map,len) != (int) len) {
			rprintf(FERROR, "write failed on %s: %s\n",
				full_fname(fname), strerror(errno));
			exit_cleanup(RERR_FILEIO);
		}
		offset += len;
	}

	if (do_progress)
		end_progress(total_size);

	if (fd != -1 && offset > 0 && sparse_end(fd) != 0) {
		rprintf(FERROR, "write failed on %s: %s\n",
			full_fname(fname), strerror(errno));
		exit_cleanup(RERR_FILEIO);
	}

	sum_end(file_sum1);

	read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
	if (verbose > 2) {
		rprintf(FINFO,"got file_sum\n");
	}
	if (fd != -1 && memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0) {
		return 0;
	}
	return 1;
}
static int receive_data(int f_in, char *fname_r, int fd_r, OFF_T size_r,
			char *fname, int fd, OFF_T total_size)
{
	static char file_sum1[MD4_SUM_LENGTH];
	static char file_sum2[MD4_SUM_LENGTH];
	struct map_struct *mapbuf;
	struct sum_struct sum;
	int32 len;
	OFF_T offset = 0;
	OFF_T offset2;
	char *data;
	int32 i;
	char *map = NULL;

	read_sum_head(f_in, &sum);

	if (fd_r >= 0 && size_r > 0) {
		int32 read_size = MAX(sum.blength * 2, 16*1024);
		mapbuf = map_file(fd_r, size_r, read_size, sum.blength);
		if (verbose > 2) {
			rprintf(FINFO, "recv mapped %s of size %.0f\n",
				fname_r, (double)size_r);
		}
	} else
		mapbuf = NULL;

	sum_init(checksum_seed);

	if (append_mode) {
		OFF_T j;
		sum.flength = (OFF_T)sum.count * sum.blength;
		if (sum.remainder)
			sum.flength -= sum.blength - sum.remainder;
		for (j = CHUNK_SIZE; j < sum.flength; j += CHUNK_SIZE) {
			if (do_progress)
				show_progress(offset, total_size);
			sum_update(map_ptr(mapbuf, offset, CHUNK_SIZE),
				   CHUNK_SIZE);
			offset = j;
		}
		if (offset < sum.flength) {
			int32 len = sum.flength - offset;
			if (do_progress)
				show_progress(offset, total_size);
			sum_update(map_ptr(mapbuf, offset, len), len);
			offset = sum.flength;
		}
		if (fd != -1 && do_lseek(fd, offset, SEEK_SET) != offset) {
			rsyserr(FERROR, errno, "lseek failed on %s",
				full_fname(fname));
			exit_cleanup(RERR_FILEIO);
		}
	}

	while ((i = recv_token(f_in, &data)) != 0) {
		if (do_progress)
			show_progress(offset, total_size);

		if (i > 0) {
			if (verbose > 3) {
				rprintf(FINFO,"data recv %d at %.0f\n",
					i,(double)offset);
			}

			stats.literal_data += i;
			cleanup_got_literal = 1;

			sum_update(data, i);

			if (fd != -1 && write_file(fd,data,i) != i)
				goto report_write_error;
			offset += i;
			continue;
		}

		i = -(i+1);
		offset2 = i * (OFF_T)sum.blength;
		len = sum.blength;
		if (i == (int)sum.count-1 && sum.remainder != 0)
			len = sum.remainder;

		stats.matched_data += len;

		if (verbose > 3) {
			rprintf(FINFO,
				"chunk[%d] of size %ld at %.0f offset=%.0f\n",
				i, (long)len, (double)offset2, (double)offset);
		}

		if (mapbuf) {
			map = map_ptr(mapbuf,offset2,len);

			see_token(map, len);
			sum_update(map, len);
		}

		if (inplace) {
			if (offset == offset2 && fd != -1) {
				if (flush_write_file(fd) < 0)
					goto report_write_error;
				offset += len;
				if (do_lseek(fd, len, SEEK_CUR) != offset) {
					rsyserr(FERROR, errno,
						"lseek failed on %s",
						full_fname(fname));
					exit_cleanup(RERR_FILEIO);
				}
				continue;
			}
		}
		if (fd != -1 && map && write_file(fd, map, len) != (int)len)
			goto report_write_error;
		offset += len;
	}

	if (flush_write_file(fd) < 0)
		goto report_write_error;

#ifdef HAVE_FTRUNCATE
	if (inplace && fd != -1)
		ftruncate(fd, offset);
#endif

	if (do_progress)
		end_progress(total_size);

	if (fd != -1 && offset > 0 && sparse_end(fd) != 0) {
	    report_write_error:
		rsyserr(FERROR, errno, "write failed on %s",
			full_fname(fname));
		exit_cleanup(RERR_FILEIO);
	}

	sum_end(file_sum1);

	if (mapbuf)
		unmap_file(mapbuf);

	read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
	if (verbose > 2)
		rprintf(FINFO,"got file_sum\n");
	if (fd != -1 && memcmp(file_sum1, file_sum2, MD4_SUM_LENGTH) != 0)
		return 0;
	return 1;
}
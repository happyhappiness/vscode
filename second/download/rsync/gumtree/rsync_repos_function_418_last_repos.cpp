static int receive_data(int f_in, char *fname_r, int fd_r, OFF_T size_r,
			const char *fname, int fd, OFF_T total_size)
{
	static char file_sum1[MAX_DIGEST_LEN];
	struct map_struct *mapbuf;
	struct sum_struct sum;
	int32 len;
	OFF_T offset = 0;
	OFF_T offset2;
	char *data;
	int32 i;
	char *map = NULL;
#ifdef SUPPORT_PREALLOCATION
#ifdef PREALLOCATE_NEEDS_TRUNCATE
	OFF_T preallocated_len = 0;
#endif

	if (preallocate_files && fd != -1 && total_size > 0 && (!inplace || total_size > size_r)) {
		/* Try to preallocate enough space for file's eventual length.  Can
		 * reduce fragmentation on filesystems like ext4, xfs, and NTFS. */
		if (do_fallocate(fd, 0, total_size) == 0) {
#ifdef PREALLOCATE_NEEDS_TRUNCATE
			preallocated_len = total_size;
#endif
		} else
			rsyserr(FWARNING, errno, "do_fallocate %s", full_fname(fname));
	}
#endif

	read_sum_head(f_in, &sum);

	if (fd_r >= 0 && size_r > 0) {
		int32 read_size = MAX(sum.blength * 2, 16*1024);
		mapbuf = map_file(fd_r, size_r, read_size, sum.blength);
		if (DEBUG_GTE(DELTASUM, 2)) {
			rprintf(FINFO, "recv mapped %s of size %s\n",
				fname_r, big_num(size_r));
		}
	} else
		mapbuf = NULL;

	sum_init(checksum_seed);

	if (append_mode > 0) {
		OFF_T j;
		sum.flength = (OFF_T)sum.count * sum.blength;
		if (sum.remainder)
			sum.flength -= sum.blength - sum.remainder;
		if (append_mode == 2 && mapbuf) {
			for (j = CHUNK_SIZE; j < sum.flength; j += CHUNK_SIZE) {
				if (INFO_GTE(PROGRESS, 1))
					show_progress(offset, total_size);
				sum_update(map_ptr(mapbuf, offset, CHUNK_SIZE),
					   CHUNK_SIZE);
				offset = j;
			}
			if (offset < sum.flength) {
				int32 len = (int32)(sum.flength - offset);
				if (INFO_GTE(PROGRESS, 1))
					show_progress(offset, total_size);
				sum_update(map_ptr(mapbuf, offset, len), len);
			}
		}
		offset = sum.flength;
		if (fd != -1 && (j = do_lseek(fd, offset, SEEK_SET)) != offset) {
			rsyserr(FERROR_XFER, errno, "lseek of %s returned %s, not %s",
				full_fname(fname), big_num(j), big_num(offset));
			exit_cleanup(RERR_FILEIO);
		}
	}

	while ((i = recv_token(f_in, &data)) != 0) {
		if (INFO_GTE(PROGRESS, 1))
			show_progress(offset, total_size);

		if (allowed_lull)
			maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH | MSK_ACTIVE_RECEIVER);

		if (i > 0) {
			if (DEBUG_GTE(DELTASUM, 3)) {
				rprintf(FINFO,"data recv %d at %s\n",
					i, big_num(offset));
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

		if (DEBUG_GTE(DELTASUM, 3)) {
			rprintf(FINFO,
				"chunk[%d] of size %ld at %s offset=%s%s\n",
				i, (long)len, big_num(offset2), big_num(offset),
				updating_basis_or_equiv && offset == offset2 ? " (seek)" : "");
		}

		if (mapbuf) {
			map = map_ptr(mapbuf,offset2,len);

			see_token(map, len);
			sum_update(map, len);
		}

		if (updating_basis_or_equiv) {
			if (offset == offset2 && fd != -1) {
				OFF_T pos;
				if (flush_write_file(fd) < 0)
					goto report_write_error;
				offset += len;
				if ((pos = do_lseek(fd, len, SEEK_CUR)) != offset) {
					rsyserr(FERROR_XFER, errno,
						"lseek of %s returned %s, not %s",
						full_fname(fname),
						big_num(pos), big_num(offset));
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
	/* inplace: New data could be shorter than old data.
	 * preallocate_files: total_size could have been an overestimate.
	 *     Cut off any extra preallocated zeros from dest file. */
	if ((inplace
#ifdef PREALLOCATE_NEEDS_TRUNCATE
	  || preallocated_len > offset
#endif
	  ) && fd != -1 && do_ftruncate(fd, offset) < 0) {
		rsyserr(FERROR_XFER, errno, "ftruncate failed on %s",
			full_fname(fname));
	}
#endif

	if (INFO_GTE(PROGRESS, 1))
		end_progress(total_size);

	if (fd != -1 && offset > 0 && sparse_end(fd, offset) != 0) {
	    report_write_error:
		rsyserr(FERROR_XFER, errno, "write failed on %s",
			full_fname(fname));
		exit_cleanup(RERR_FILEIO);
	}

	if (sum_end(file_sum1) != checksum_len)
		overflow_exit("checksum_len"); /* Impossible... */

	if (mapbuf)
		unmap_file(mapbuf);

	read_buf(f_in, sender_file_sum, checksum_len);
	if (DEBUG_GTE(DELTASUM, 2))
		rprintf(FINFO,"got file_sum\n");
	if (fd != -1 && memcmp(file_sum1, sender_file_sum, checksum_len) != 0)
		return 0;
	return 1;
}
	else
		return local_server;
}


/*
 * Generate and send a stream of signatures/checksums that describe a buffer
 *
 * Generate approximately one checksum every block_len bytes.
 */
static void generate_and_send_sums(struct map_struct *buf, OFF_T len,
				   int block_len, int f_out)
{
	size_t i;
	struct sum_struct sum;
	OFF_T offset = 0;

	sum.count = (len + (block_len - 1)) / block_len;
	sum.remainder = (len % block_len);
	sum.n = block_len;
	sum.flength = len;
	/* not needed here  sum.sums = NULL; */

	if (sum.count && verbose > 3) {
		rprintf(FINFO, "count=%ld rem=%ld n=%ld flength=%.0f\n",
			(long) sum.count, (long) sum.remainder,
			(long) sum.n, (double) sum.flength);
	}

	write_int(f_out, sum.count);
	write_int(f_out, sum.n);
	write_int(f_out, sum.remainder);

	for (i = 0; i < sum.count; i++) {
		int n1 = MIN(len, block_len);
		char *map = map_ptr(buf, offset, n1);
		uint32 sum1 = get_checksum1(map, n1);
		char sum2[SUM_LENGTH];

		get_checksum2(map, n1, sum2);

		if (verbose > 3) {
			rprintf(FINFO,
				"chunk[%d] offset=%.0f len=%d sum1=%08lx\n",
				i, (double) offset, n1, (unsigned long) sum1);
		}
		write_int(f_out, sum1);
		write_buf(f_out, sum2, csum_length);
		len -= n1;
		offset += n1;
	}
}



/**
 * Acts on file number @p i from @p flist, whose name is @p fname.
 *
 * First fixes up permissions, then generates checksums for the file.
 *
 * @note This comment was added later by mbp who was trying to work it
 * out.  It might be wrong.
 **/ 
void recv_generator(char *fname, struct file_list *flist, int i, int f_out)
{  
	int fd;
	STRUCT_STAT st;
	struct map_struct *buf;
	int statret;
	struct file_struct *file = flist->files[i];
	char *fnamecmp;
	char fnamecmpbuf[MAXPATHLEN];
	extern char *compare_dest;
	extern int list_only;
	extern int preserve_perms;
	extern int only_existing;
	extern int orig_umask;

	if (list_only) return;

	if (verbose > 2)
		rprintf(FINFO,"recv_generator(%s,%d)\n",fname,i);


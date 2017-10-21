extern int csum_length;
extern int read_batch;
extern int write_batch;
extern int batch_gen_fd;
extern int protocol_version;
extern int relative_paths;
extern int keep_dirlinks;
extern int preserve_hard_links;
extern int preserve_perms;
extern int io_error;
extern int basis_dir_cnt;
extern int make_backups;
extern int cleanup_got_literal;
extern int remove_sent_files;
extern int module_id;
extern int ignore_errors;
extern int orig_umask;
extern int keep_partial;
extern int checksum_seed;
extern int inplace;
extern int delay_updates;
extern struct stats stats;
extern char *log_format;
extern char *tmpdir;
extern char *partial_dir;
extern char *basis_dir[];
extern struct file_list *the_file_list;
extern struct filter_list_struct server_filter_list;

#define SLOT_SIZE	(16*1024)	/* Desired size in bytes */
#define PER_SLOT_BITS	(SLOT_SIZE * 8) /* Number of bits per slot */
#define PER_SLOT_INTS	(SLOT_SIZE / 4) /* Number of int32s per slot */

static uint32 **delayed_bits = NULL;
static int delayed_slot_cnt = 0;
static int phase = 0;

static void init_delayed_bits(int max_ndx)
{
	delayed_slot_cnt = (max_ndx + PER_SLOT_BITS - 1) / PER_SLOT_BITS;

	if (!(delayed_bits = (uint32**)calloc(delayed_slot_cnt, sizeof (uint32*))))
		out_of_memory("set_delayed_bit");
}

static void set_delayed_bit(int ndx)
{
	int slot = ndx / PER_SLOT_BITS;
	ndx %= PER_SLOT_BITS;

	if (!delayed_bits[slot]) {
		if (!(delayed_bits[slot] = (uint32*)calloc(PER_SLOT_INTS, 4)))
			out_of_memory("set_delayed_bit");
	}

	delayed_bits[slot][ndx/32] |= 1u << (ndx % 32);
}

/* Call this with -1 to start checking from 0.  Returns -1 at the end. */
static int next_delayed_bit(int after)
{
	uint32 bits, mask;
	int i, ndx = after + 1;
	int slot = ndx / PER_SLOT_BITS;
	ndx %= PER_SLOT_BITS;

	mask = (1u << (ndx % 32)) - 1;
	for (i = ndx / 32; slot < delayed_slot_cnt; slot++, i = mask = 0) {
		if (!delayed_bits[slot])
			continue;
		for ( ; i < PER_SLOT_INTS; i++, mask = 0) {
			if (!(bits = delayed_bits[slot][i] & ~mask))
				continue;
			/* The xor magic figures out the lowest enabled bit in
			 * bits, and the switch quickly computes log2(bit). */
			switch (bits ^ (bits & (bits-1))) {
#define LOG2(n) case 1u << n: return slot*PER_SLOT_BITS + i*32 + n
			    LOG2(0);  LOG2(1);  LOG2(2);  LOG2(3);
			    LOG2(4);  LOG2(5);  LOG2(6);  LOG2(7);
			    LOG2(8);  LOG2(9);  LOG2(10); LOG2(11);
			    LOG2(12); LOG2(13); LOG2(14); LOG2(15);
			    LOG2(16); LOG2(17); LOG2(18); LOG2(19);
			    LOG2(20); LOG2(21); LOG2(22); LOG2(23);
			    LOG2(24); LOG2(25); LOG2(26); LOG2(27);
			    LOG2(28); LOG2(29); LOG2(30); LOG2(31);
			}
			return -1; /* impossible... */
		}
	}

	return -1;
}


/*
 * get_tmpname() - create a tmp filename for a given filename
 *
 *   If a tmpdir is defined, use that as the directory to
 *   put it in.  Otherwise, the tmp filename is in the same

/* -*- c-file-style: "linux" -*-

   Weiss 1/1999
   Batch utilities for rsync.

*/

#include "rsync.h"
#include <time.h>

extern char *batch_prefix;
extern int csum_length;
extern int protocol_version;
extern struct stats stats;

struct file_list *batch_flist;

static char rsync_flist_file[] = ".rsync_flist";
static char rsync_csums_file[] = ".rsync_csums";
static char rsync_delta_file[] = ".rsync_delta";
static char rsync_argvs_file[] = ".rsync_argvs";

static int f_csums = -1;
static int f_delta = -1;

void write_batch_flist_info(int flist_count, struct file_struct **files)
{
	char filename[MAXPATHLEN];
	int i, f, save_pv;
	int64 save_written;

	stringjoin(filename, sizeof filename,
	    batch_prefix, rsync_flist_file, NULL);

	f = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (f < 0) {
		rprintf(FERROR, "Batch file %s open error: %s\n",
		    filename, strerror(errno));
		exit_cleanup(1);
	}

	save_written = stats.total_written;
	save_pv = protocol_version;
	protocol_version = PROTOCOL_VERSION;
	write_int(f, protocol_version);
	write_int(f, flist_count);

	for (i = 0; i < flist_count; i++) {
		send_file_entry(files[i], f,
		    files[i]->flags & FLAG_TOP_DIR ?  XMIT_TOP_DIR : 0);
	}
	send_file_entry(NULL, f, 0);

	protocol_version = save_pv;
	stats.total_written = save_written;

	close(f);
}


void write_batch_argvs_file(int argc, char *argv[])
{
	int f;
	int i;
	char buff[256]; /* XXX */
	char buff2[MAXPATHLEN + 6];
	char filename[MAXPATHLEN];

	stringjoin(filename, sizeof filename,
	    batch_prefix, rsync_argvs_file, NULL);

	f = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
	    S_IRUSR | S_IWUSR | S_IEXEC);
	if (f < 0) {
		rprintf(FERROR, "Batch file %s open error: %s\n",
		    filename, strerror(errno));
		exit_cleanup(1);
	}
	buff[0] = '\0';

	/* Write argvs info to batch file */

	for (i = 0; i < argc; ++i) {
		if (i == argc - 2) /* Skip source directory on cmdline */
			continue;
		/*
		 * FIXME:
		 * I think directly manipulating argv[] is probably bogus
		 */
		if (!strncmp(argv[i], "--write-batch",
		    strlen("--write-batch"))) {
			/* Safer to change it here than script */
			/*
			 * Change to --read-batch=prefix
			 * to get ready for remote
			 */
			strlcat(buff, "--read-batch=", sizeof buff);
			strlcat(buff, batch_prefix, sizeof buff);
		} else
		if (i == argc - 1) {
			snprintf(buff2, sizeof buff2, "${1:-%s}", argv[i]);
			strlcat(buff, buff2, sizeof buff);
		}
		else {
			strlcat(buff, argv[i], sizeof buff);
		}

		if (i < (argc - 1)) {
			strlcat(buff, " ", sizeof buff);
		}
	}
	strlcat(buff, "\n", sizeof buff);
	if (!write(f, buff, strlen(buff))) {
		rprintf(FERROR, "Batch file %s write error: %s\n",
		    filename, strerror(errno));
		close(f);
		exit_cleanup(1);
	}
	close(f);
}

struct file_list *create_flist_from_batch(void)
{
	char filename[MAXPATHLEN];
	unsigned short flags;
	int i, f, save_pv;
	int64 save_read;

	stringjoin(filename, sizeof filename,
	    batch_prefix, rsync_flist_file, NULL);

	f = do_open(filename, O_RDONLY, 0);
	if (f < 0) {
		rprintf(FERROR, "Batch file %s open error: %s\n",
		    filename, strerror(errno));
		exit_cleanup(1);
	}

	batch_flist = flist_new(WITH_HLINK, "create_flist_from_batch");

	save_read = stats.total_read;
	save_pv = protocol_version;
	protocol_version = read_int(f);

	batch_flist->count = read_int(f);
	flist_expand(batch_flist);

	for (i = 0; (flags = read_byte(f)) != 0; i++) {
		if (protocol_version >= 28 && (flags & XMIT_EXTENDED_FLAGS))
			flags |= read_byte(f) << 8;
		receive_file_entry(&batch_flist->files[i], flags, batch_flist, f);
	}
	receive_file_entry(NULL, 0, NULL, 0); /* Signal that we're done. */

	protocol_version = save_pv;
	stats.total_read = save_read;

	return batch_flist;
}

void write_batch_csums_file(void *buff, int bytes_to_write)
{
	if (write(f_csums, buff, bytes_to_write) < 0) {
		rprintf(FERROR, "Batch file write error: %s\n",
		    strerror(errno));
		close(f_csums);
		exit_cleanup(1);
	}
}

void close_batch_csums_file(void)
{
	close(f_csums);
	f_csums = -1;
}


/**
 * Write csum info to batch file
 *
 * @todo This will break if s->count is ever larger than maxint.  The
 * batch code should probably be changed to consistently use the
 * variable-length integer routines, which is probably a compatible
 * change.
 **/
void write_batch_csum_info(int *flist_entry, struct sum_struct *s)
{
	size_t i;
	int int_count;
	char filename[MAXPATHLEN];

	if (f_csums < 0) {
		stringjoin(filename, sizeof filename,
		    batch_prefix, rsync_csums_file, NULL);

		f_csums = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		    S_IRUSR | S_IWUSR);
		if (f_csums < 0) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
			    filename, strerror(errno));
			close(f_csums);
			exit_cleanup(1);
		}
	}

	write_batch_csums_file(flist_entry, sizeof (int));
	int_count = s ? (int) s->count : 0;
	write_batch_csums_file(&int_count, sizeof int_count);

	if (s) {
		for (i = 0; i < s->count; i++) {
			write_batch_csums_file(&s->sums[i].sum1,
			    sizeof (uint32));
			write_batch_csums_file(s->sums[i].sum2, csum_length);
		}
	}
}

int read_batch_csums_file(char *buff, int len)
{
	int bytes_read;

	if ((bytes_read = read(f_csums, buff, len)) < 0) {
		rprintf(FERROR, "Batch file read error: %s\n", strerror(errno));
		close(f_csums);
		exit_cleanup(1);
	}
	return bytes_read;
}

void read_batch_csum_info(int flist_entry, struct sum_struct *s,
			  int *checksums_match)
{

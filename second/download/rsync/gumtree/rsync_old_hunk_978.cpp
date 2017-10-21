 * For historical reasons this is off during the start of the
 * connection, but it's switched on quite early using
 * io_start_multiplex_out() and io_start_multiplex_in(). */

#include "rsync.h"
#include "ifuncs.h"

/** If no timeout is specified then use a 60 second select timeout */
#define SELECT_TIMEOUT 60

extern int bwlimit;
extern size_t bwlimit_writemax;
extern int io_timeout;
extern int am_server;
extern int am_daemon;
extern int am_sender;
extern int am_generator;
extern int inc_recurse;
extern int io_error;
extern int eol_nulls;
extern int flist_eof;
extern int list_only;
extern int read_batch;
extern int compat_flags;
extern int protect_args;
extern int checksum_seed;
extern int protocol_version;
extern int remove_source_files;
extern int preserve_hard_links;
extern struct stats stats;
extern struct file_list *cur_flist;
#ifdef ICONV_OPTION
extern int filesfrom_convert;
extern iconv_t ic_send, ic_recv;
#endif

int csum_length = SHORT_SUM_LENGTH; /* initial value */
int allowed_lull = 0;
int ignore_timeout = 0;
int batch_fd = -1;
int msgdone_cnt = 0;

/* Ignore an EOF error if non-zero. See whine_about_eof(). */
int kluge_around_eof = 0;

int msg_fd_in = -1;
int msg_fd_out = -1;
int sock_f_in = -1;
int sock_f_out = -1;

static int iobuf_f_in = -1;
static char *iobuf_in;
static size_t iobuf_in_siz;
static size_t iobuf_in_ndx;
static size_t iobuf_in_remaining;

static int iobuf_f_out = -1;
static char *iobuf_out;
static int iobuf_out_cnt;

int flist_forward_from = -1;

static int io_multiplexing_out;
static int io_multiplexing_in;
static time_t last_io_in;
static time_t last_io_out;
static int no_flush;

static int write_batch_monitor_in = -1;
static int write_batch_monitor_out = -1;

static int io_filesfrom_f_in = -1;
static int io_filesfrom_f_out = -1;
static xbuf ff_buf = EMPTY_XBUF;
static char ff_lastchar;
#ifdef ICONV_OPTION
static xbuf iconv_buf = EMPTY_XBUF;
#endif
static int defer_forwarding_messages = 0, keep_defer_forwarding = 0;
static int select_timeout = SELECT_TIMEOUT;
static int active_filecnt = 0;
static OFF_T active_bytecnt = 0;
static int first_message = 1;

static char int_byte_extra[64] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* (00 - 3F)/4 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* (40 - 7F)/4 */
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* (80 - BF)/4 */
	2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 6, /* (C0 - FF)/4 */
};

#define REMOTE_OPTION_ERROR "rsync: on remote machine: -"
#define REMOTE_OPTION_ERROR2 ": unknown option"

enum festatus { FES_SUCCESS, FES_REDO, FES_NO_SEND };

static void check_timeout(void)
{
	time_t t, chk;

	if (!io_timeout || ignore_timeout)
		return;

	t = time(NULL);

	if (!last_io_in)
		last_io_in = t;

	chk = MAX(last_io_out, last_io_in);
	if (t - chk >= io_timeout) {
		if (am_server || am_daemon)
			exit_cleanup(RERR_TIMEOUT);
		rprintf(FERROR, "[%s] io timeout after %d seconds -- exiting\n",
			who_am_i(), (int)(t-chk));
		exit_cleanup(RERR_TIMEOUT);
	}
}

static void readfd(int fd, char *buffer, size_t N);
static void writefd(int fd, const char *buf, size_t len);
static void writefd_unbuffered(int fd, const char *buf, size_t len);
static void mplex_write(int fd, enum msgcode code, const char *buf, size_t len, int convert);

static flist_ndx_list redo_list, hlink_list;

struct msg_list_item {
	struct msg_list_item *next;
	char convert;
	char buf[1];
};

struct msg_list {
	struct msg_list_item *head, *tail;
};

static struct msg_list msg_queue;

static void got_flist_entry_status(enum festatus status, const char *buf)
{
	int ndx = IVAL(buf, 0);
	struct file_list *flist = flist_for_ndx(ndx, "got_flist_entry_status");

	if (remove_source_files) {
		active_filecnt--;
		active_bytecnt -= F_LENGTH(flist->files[ndx - flist->ndx_start]);
	}

 * For historical reasons this is off during the start of the
 * connection, but it's switched on quite early using
 * io_start_multiplex_out() and io_start_multiplex_in(). */

#include "rsync.h"
#include "ifuncs.h"
#include "inums.h"

/** If no timeout is specified then use a 60 second select timeout */
#define SELECT_TIMEOUT 60

extern int bwlimit;
extern size_t bwlimit_writemax;
extern int io_timeout;
extern int am_server;
extern int am_sender;
extern int am_receiver;
extern int am_generator;
extern int msgs2stderr;
extern int inc_recurse;
extern int io_error;
extern int eol_nulls;
extern int flist_eof;
extern int file_total;
extern int file_old_total;
extern int list_only;
extern int read_batch;
extern int compat_flags;
extern int protect_args;
extern int checksum_seed;
extern int protocol_version;
extern int remove_source_files;
extern int preserve_hard_links;
extern BOOL extra_flist_sending_enabled;
extern BOOL flush_ok_after_signal;
extern struct stats stats;
extern struct file_list *cur_flist;
#ifdef ICONV_OPTION
extern int filesfrom_convert;
extern iconv_t ic_send, ic_recv;
#endif

int csum_length = SHORT_SUM_LENGTH; /* initial value */
int allowed_lull = 0;
int batch_fd = -1;
int msgdone_cnt = 0;
int forward_flist_data = 0;
BOOL flist_receiving_enabled = False;

/* Ignore an EOF error if non-zero. See whine_about_eof(). */
int kluge_around_eof = 0;
int got_kill_signal = -1; /* is set to 0 only after multiplexed I/O starts */

int sock_f_in = -1;
int sock_f_out = -1;

int64 total_data_read = 0;
int64 total_data_written = 0;

static struct {
	xbuf in, out, msg;
	int in_fd;
	int out_fd; /* Both "out" and "msg" go to this fd. */
	int in_multiplexed;
	unsigned out_empty_len;
	size_t raw_data_header_pos;      /* in the out xbuf */
	size_t raw_flushing_ends_before; /* in the out xbuf */
	size_t raw_input_ends_before;    /* in the in xbuf */
} iobuf = { .in_fd = -1, .out_fd = -1 };

static time_t last_io_in;
static time_t last_io_out;

static int write_batch_monitor_in = -1;
static int write_batch_monitor_out = -1;

static int ff_forward_fd = -1;
static int ff_reenable_multiplex = -1;
static char ff_lastchar = '\0';
static xbuf ff_xb = EMPTY_XBUF;
#ifdef ICONV_OPTION
static xbuf iconv_buf = EMPTY_XBUF;
#endif
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

/* Our I/O buffers are sized with no bits on in the lowest byte of the "size"
 * (indeed, our rounding of sizes in 1024-byte units assures more than this).
 * This allows the code that is storing bytes near the physical end of a
 * circular buffer to temporarily reduce the buffer's size (in order to make
 * some storing idioms easier), while also making it simple to restore the
 * buffer's actual size when the buffer's "pos" wraps around to the start (we
 * just round the buffer's size up again). */

#define IOBUF_WAS_REDUCED(siz) ((siz) & 0xFF)
#define IOBUF_RESTORE_SIZE(siz) (((siz) | 0xFF) + 1)

#define IN_MULTIPLEXED (iobuf.in_multiplexed != 0)
#define IN_MULTIPLEXED_AND_READY (iobuf.in_multiplexed > 0)
#define OUT_MULTIPLEXED (iobuf.out_empty_len != 0)

#define PIO_NEED_INPUT (1<<0) /* The *_NEED_* flags are mutually exclusive. */
#define PIO_NEED_OUTROOM (1<<1)
#define PIO_NEED_MSGROOM (1<<2)

#define PIO_CONSUME_INPUT (1<<4) /* Must becombined with PIO_NEED_INPUT. */

#define PIO_INPUT_AND_CONSUME (PIO_NEED_INPUT | PIO_CONSUME_INPUT)
#define PIO_NEED_FLAGS (PIO_NEED_INPUT | PIO_NEED_OUTROOM | PIO_NEED_MSGROOM)

#define REMOTE_OPTION_ERROR "rsync: on remote machine: -"
#define REMOTE_OPTION_ERROR2 ": unknown option"

#define FILESFROM_BUFLEN 2048

enum festatus { FES_SUCCESS, FES_REDO, FES_NO_SEND };

static flist_ndx_list redo_list, hlink_list;

static void read_a_msg(void);
static void drain_multiplex_messages(void);
static void sleep_for_bwlimit(int bytes_written);

static void check_timeout(BOOL allow_keepalive)
{
	time_t t, chk;

	/* On the receiving side, the generator is now the one that decides
	 * when a timeout has occurred.  When it is sifting through a lot of
	 * files looking for work, it will be sending keep-alive messages to
	 * the sender, and even though the receiver won't be sending/receiving
	 * anything (not even keep-alive messages), the successful writes to
	 * the sender will keep things going.  If the receiver is actively
	 * receiving data, it will ensure that the generator knows that it is
	 * not idle by sending the generator keep-alive messages (since the
	 * generator might be blocked trying to send checksums, it needs to
	 * know that the receiver is active).  Thus, as long as one or the
	 * other is successfully doing work, the generator will not timeout. */
	if (!io_timeout)
		return;

	t = time(NULL);

	if (allow_keepalive) {
		/* This may put data into iobuf.msg w/o flushing. */
		maybe_send_keepalive(t, 0);
	}

	if (!last_io_in)
		last_io_in = t;

	if (am_receiver)
		return;

	chk = MAX(last_io_out, last_io_in);
	if (t - chk >= io_timeout) {
		if (am_server)
			msgs2stderr = 1;
		rprintf(FERROR, "[%s] io timeout after %d seconds -- exiting\n",
			who_am_i(), (int)(t-chk));
		exit_cleanup(RERR_TIMEOUT);
	}
}

/* It's almost always an error to get an EOF when we're trying to read from the
 * network, because the protocol is (for the most part) self-terminating.
 *
 * There is one case for the receiver when it is at the end of the transfer
 * (hanging around reading any keep-alive packets that might come its way): if
 * the sender dies before the generator's kill-signal comes through, we can end
 * up here needing to loop until the kill-signal arrives.  In this situation,
 * kluge_around_eof will be < 0.
 *
 * There is another case for older protocol versions (< 24) where the module
 * listing was not terminated, so we must ignore an EOF error in that case and
 * exit.  In this situation, kluge_around_eof will be > 0. */
static NORETURN void whine_about_eof(BOOL allow_kluge)
{
	if (kluge_around_eof && allow_kluge) {
		int i;
		if (kluge_around_eof > 0)
			exit_cleanup(0);
		/* If we're still here after 10 seconds, exit with an error. */
		for (i = 10*1000/20; i--; )
			msleep(20);
	}

	rprintf(FERROR, RSYNC_NAME ": connection unexpectedly closed "
		"(%s bytes received so far) [%s]\n",
		big_num(stats.total_read), who_am_i());

	exit_cleanup(RERR_STREAMIO);
}

/* Do a safe read, handling any needed looping and error handling.
 * Returns the count of the bytes read, which will only be different
 * from "len" if we encountered an EOF.  This routine is not used on
 * the socket except very early in the transfer. */
static size_t safe_read(int fd, char *buf, size_t len)
{
	size_t got;
	int n;

	assert(fd != iobuf.in_fd);

	n = read(fd, buf, len);
	if ((size_t)n == len || n == 0) {
		if (DEBUG_GTE(IO, 2))
			rprintf(FINFO, "[%s] safe_read(%d)=%ld\n", who_am_i(), fd, (long)n);
		return n;
	}
	if (n < 0) {
		if (errno != EINTR && errno != EWOULDBLOCK && errno != EAGAIN) {
		  read_failed:
			rsyserr(FERROR, errno, "safe_read failed to read %ld bytes [%s]",
				(long)len, who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}
		got = 0;
	} else
		got = n;

	while (1) {
		struct timeval tv;
		fd_set r_fds, e_fds;
		int cnt;

		FD_ZERO(&r_fds);
		FD_SET(fd, &r_fds);
		FD_ZERO(&e_fds);
		FD_SET(fd, &e_fds);
		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		cnt = select(fd+1, &r_fds, NULL, &e_fds, &tv);
		if (cnt <= 0) {
			if (cnt < 0 && errno == EBADF) {
				rsyserr(FERROR, errno, "safe_read select failed [%s]",
					who_am_i());
				exit_cleanup(RERR_FILEIO);
			}
			if (io_timeout)
				maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
			continue;
		}

		/*if (FD_ISSET(fd, &e_fds))
			rprintf(FINFO, "select exception on fd %d\n", fd); */

		if (FD_ISSET(fd, &r_fds)) {
			n = read(fd, buf + got, len - got);
			if (DEBUG_GTE(IO, 2))
				rprintf(FINFO, "[%s] safe_read(%d)=%ld\n", who_am_i(), fd, (long)n);
			if (n == 0)
				break;
			if (n < 0) {
				if (errno == EINTR)
					continue;
				goto read_failed;
			}
			if ((got += (size_t)n) == len)
				break;
		}
	}

	return got;
}

static const char *what_fd_is(int fd)
{
	static char buf[20];

	if (fd == sock_f_out)
		return "socket";
	else if (fd == iobuf.out_fd)
		return "message fd";
	else if (fd == batch_fd)
		return "batch file";
	else {
		snprintf(buf, sizeof buf, "fd %d", fd);
		return buf;
	}
}

/* Do a safe write, handling any needed looping and error handling.
 * Returns only if everything was successfully written.  This routine
 * is not used on the socket except very early in the transfer. */
static void safe_write(int fd, const char *buf, size_t len)
{
	int n;

	assert(fd != iobuf.out_fd);

	n = write(fd, buf, len);
	if ((size_t)n == len)
		return;
	if (n < 0) {
		if (errno != EINTR && errno != EWOULDBLOCK && errno != EAGAIN) {
		  write_failed:
			rsyserr(FERROR, errno,
				"safe_write failed to write %ld bytes to %s [%s]",
				(long)len, what_fd_is(fd), who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}
	} else {
		buf += n;
		len -= n;
	}

	while (len) {
		struct timeval tv;
		fd_set w_fds;
		int cnt;

		FD_ZERO(&w_fds);
		FD_SET(fd, &w_fds);
		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		cnt = select(fd + 1, NULL, &w_fds, NULL, &tv);
		if (cnt <= 0) {
			if (cnt < 0 && errno == EBADF) {
				rsyserr(FERROR, errno, "safe_write select failed on %s [%s]",
					what_fd_is(fd), who_am_i());
				exit_cleanup(RERR_FILEIO);
			}
			if (io_timeout)
				maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
			continue;
		}

		if (FD_ISSET(fd, &w_fds)) {
			n = write(fd, buf, len);
			if (n < 0) {
				if (errno == EINTR)
					continue;
				goto write_failed;
			}
			buf += n;
			len -= n;
		}
	}
}

/* This is only called when files-from data is known to be available.  We read
 * a chunk of data and put it into the output buffer. */
static void forward_filesfrom_data(void)
{
	int len;

	len = read(ff_forward_fd, ff_xb.buf + ff_xb.len, ff_xb.size - ff_xb.len);
	if (len <= 0) {
		if (len == 0 || errno != EINTR) {
			/* Send end-of-file marker */
			ff_forward_fd = -1;
			write_buf(iobuf.out_fd, "\0\0", ff_lastchar ? 2 : 1);
			free_xbuf(&ff_xb);
			if (ff_reenable_multiplex >= 0)
				io_start_multiplex_out(ff_reenable_multiplex);
		}
		return;
	}

	if (DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] files-from read=%ld\n", who_am_i(), (long)len);

#ifdef ICONV_OPTION
	len += ff_xb.len;
#endif

	if (!eol_nulls) {
		char *s = ff_xb.buf + len;
		/* Transform CR and/or LF into '\0' */
		while (s-- > ff_xb.buf) {
			if (*s == '\n' || *s == '\r')
				*s = '\0';
		}
	}

	if (ff_lastchar)
		ff_xb.pos = 0;
	else {
		char *s = ff_xb.buf;
		/* Last buf ended with a '\0', so don't let this buf start with one. */
		while (len && *s == '\0')
			s++, len--;
		ff_xb.pos = s - ff_xb.buf;
	}

#ifdef ICONV_OPTION
	if (filesfrom_convert && len) {
		char *sob = ff_xb.buf + ff_xb.pos, *s = sob;
		char *eob = sob + len;
		int flags = ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE | ICB_CIRCULAR_OUT;
		if (ff_lastchar == '\0')
			flags |= ICB_INIT;
		/* Convert/send each null-terminated string separately, skipping empties. */
		while (s != eob) {
			if (*s++ == '\0') {
				ff_xb.len = s - sob - 1;
				if (iconvbufs(ic_send, &ff_xb, &iobuf.out, flags) < 0)
					exit_cleanup(RERR_PROTOCOL); /* impossible? */
				write_buf(iobuf.out_fd, s-1, 1); /* Send the '\0'. */
				while (s != eob && *s == '\0')
					s++;
				sob = s;
				ff_xb.pos = sob - ff_xb.buf;
				flags |= ICB_INIT;
			}
		}

		if ((ff_xb.len = s - sob) == 0)
			ff_lastchar = '\0';
		else {
			/* Handle a partial string specially, saving any incomplete chars. */
			flags &= ~ICB_INCLUDE_INCOMPLETE;
			if (iconvbufs(ic_send, &ff_xb, &iobuf.out, flags) < 0) {
				if (errno == E2BIG)
					exit_cleanup(RERR_PROTOCOL); /* impossible? */
				if (ff_xb.pos)
					memmove(ff_xb.buf, ff_xb.buf + ff_xb.pos, ff_xb.len);
			}
			ff_lastchar = 'x'; /* Anything non-zero. */
		}
	} else
#endif

	if (len) {
		char *f = ff_xb.buf + ff_xb.pos;
		char *t = ff_xb.buf;
		char *eob = f + len;
		/* Eliminate any multi-'\0' runs. */
		while (f != eob) {
			if (!(*t++ = *f++)) {
				while (f != eob && *f == '\0')
					f++;
			}
		}
		ff_lastchar = f[-1];
		if ((len = t - ff_xb.buf) != 0) {
			/* This will not circle back to perform_io() because we only get
			 * called when there is plenty of room in the output buffer. */
			write_buf(iobuf.out_fd, ff_xb.buf, len);
		}
	}
}

void reduce_iobuf_size(xbuf *out, size_t new_size)
{
	if (new_size < out->size) {
		/* Avoid weird buffer interactions by only outputting this to stderr. */
		if (msgs2stderr && DEBUG_GTE(IO, 4)) {
			const char *name = out == &iobuf.out ? "iobuf.out"
					 : out == &iobuf.msg ? "iobuf.msg"
					 : NULL;
			if (name) {
				rprintf(FINFO, "[%s] reduced size of %s (-%d)\n",
					who_am_i(), name, (int)(out->size - new_size));
			}
		}
		out->size = new_size;
	}
}

void restore_iobuf_size(xbuf *out)
{
	if (IOBUF_WAS_REDUCED(out->size)) {
		size_t new_size = IOBUF_RESTORE_SIZE(out->size);
		/* Avoid weird buffer interactions by only outputting this to stderr. */
		if (msgs2stderr && DEBUG_GTE(IO, 4)) {
			const char *name = out == &iobuf.out ? "iobuf.out"
					 : out == &iobuf.msg ? "iobuf.msg"
					 : NULL;
			if (name) {
				rprintf(FINFO, "[%s] restored size of %s (+%d)\n",
					who_am_i(), name, (int)(new_size - out->size));
			}
		}
		out->size = new_size;
	}
}

static void handle_kill_signal(BOOL flush_ok)
{
	got_kill_signal = -1;
	flush_ok_after_signal = flush_ok;
	exit_cleanup(RERR_SIGNAL);
}

/* Perform buffered input and/or output until specified conditions are met.
 * When given a "needed" read or write request, this returns without doing any
 * I/O if the needed input bytes or write space is already available.  Once I/O
 * is needed, this will try to do whatever reading and/or writing is currently
 * possible, up to the maximum buffer allowances, no matter if this is a read
 * or write request.  However, the I/O stops as soon as the required input
 * bytes or output space is available.  If this is not a read request, the
 * routine may also do some advantageous reading of messages from a multiplexed
 * input source (which ensures that we don't jam up with everyone in their
 * "need to write" code and nobody reading the accumulated data that would make
 * writing possible).
 *
 * The iobuf.in, .out and .msg buffers are all circular.  Callers need to be
 * aware that some data copies will need to be split when the bytes wrap around
 * from the end to the start.  In order to help make writing into the output
 * buffers easier for some operations (such as the use of SIVAL() into the
 * buffer) a buffer may be temporarily shortened by a small amount, but the
 * original size will be automatically restored when the .pos wraps to the
 * start.  See also the 3 raw_* iobuf vars that are used in the handling of
 * MSG_DATA bytes as they are read-from/written-into the buffers.
 *
 * When writing, we flush data in the following priority order:
 *
 * 1. Finish writing any in-progress MSG_DATA sequence from iobuf.out.
 *
 * 2. Write out all the messages from the message buf (if iobuf.msg is active).
 *    Yes, this means that a PIO_NEED_OUTROOM call will completely flush any
 *    messages before getting to the iobuf.out flushing (except for rule 1).
 *
 * 3. Write out the raw data from iobuf.out, possibly filling in the multiplexed
 *    MSG_DATA header that was pre-allocated (when output is multiplexed).
 *
 * TODO:  items for possible future work:
 *
 *    - Make this routine able to read the generator-to-receiver batch flow?
 *
 * Unlike the old routines that this replaces, it is OK to read ahead as far as
 * we can because the read_a_msg() routine now reads its bytes out of the input
 * buffer.  In the old days, only raw data was in the input buffer, and any
 * unused raw data in the buf would prevent the reading of socket data. */
static char *perform_io(size_t needed, int flags)
{
	fd_set r_fds, e_fds, w_fds;
	struct timeval tv;
	int cnt, max_fd;
	size_t empty_buf_len = 0;
	xbuf *out;
	char *data;

	if (iobuf.in.len == 0 && iobuf.in.pos != 0) {
		if (iobuf.raw_input_ends_before)
			iobuf.raw_input_ends_before -= iobuf.in.pos;
		iobuf.in.pos = 0;
	}

	switch (flags & PIO_NEED_FLAGS) {
	case PIO_NEED_INPUT:
		/* We never resize the circular input buffer. */
		if (iobuf.in.size < needed) {
			rprintf(FERROR, "need to read %ld bytes, iobuf.in.buf is only %ld bytes.\n",
				(long)needed, (long)iobuf.in.size);
			exit_cleanup(RERR_PROTOCOL);
		}

		if (msgs2stderr && DEBUG_GTE(IO, 3)) {
			rprintf(FINFO, "[%s] perform_io(%ld, %sinput)\n",
				who_am_i(), (long)needed, flags & PIO_CONSUME_INPUT ? "consume&" : "");
		}
		break;

	case PIO_NEED_OUTROOM:
		/* We never resize the circular output buffer. */
		if (iobuf.out.size - iobuf.out_empty_len < needed) {
			fprintf(stderr, "need to write %ld bytes, iobuf.out.buf is only %ld bytes.\n",
				(long)needed, (long)(iobuf.out.size - iobuf.out_empty_len));
			exit_cleanup(RERR_PROTOCOL);
		}

		if (msgs2stderr && DEBUG_GTE(IO, 3)) {
			rprintf(FINFO, "[%s] perform_io(%ld, outroom) needs to flush %ld\n",
				who_am_i(), (long)needed,
				iobuf.out.len + needed > iobuf.out.size
				? (long)(iobuf.out.len + needed - iobuf.out.size) : 0L);
		}
		break;

	case PIO_NEED_MSGROOM:
		/* We never resize the circular message buffer. */
		if (iobuf.msg.size < needed) {
			fprintf(stderr, "need to write %ld bytes, iobuf.msg.buf is only %ld bytes.\n",
				(long)needed, (long)iobuf.msg.size);
			exit_cleanup(RERR_PROTOCOL);
		}

		if (msgs2stderr && DEBUG_GTE(IO, 3)) {
			rprintf(FINFO, "[%s] perform_io(%ld, msgroom) needs to flush %ld\n",
				who_am_i(), (long)needed,
				iobuf.msg.len + needed > iobuf.msg.size
				? (long)(iobuf.msg.len + needed - iobuf.msg.size) : 0L);
		}
		break;

	case 0:
		if (msgs2stderr && DEBUG_GTE(IO, 3))
			rprintf(FINFO, "[%s] perform_io(%ld, %d)\n", who_am_i(), (long)needed, flags);
		break;

	default:
		exit_cleanup(RERR_UNSUPPORTED);
	}

	while (1) {
		switch (flags & PIO_NEED_FLAGS) {
		case PIO_NEED_INPUT:
			if (iobuf.in.len >= needed)
				goto double_break;
			break;
		case PIO_NEED_OUTROOM:
			/* Note that iobuf.out_empty_len doesn't factor into this check
			 * because iobuf.out.len already holds any needed header len. */
			if (iobuf.out.len + needed <= iobuf.out.size)
				goto double_break;
			break;
		case PIO_NEED_MSGROOM:
			if (iobuf.msg.len + needed <= iobuf.msg.size)
				goto double_break;
			break;
		}

		max_fd = -1;

		FD_ZERO(&r_fds);
		FD_ZERO(&e_fds);
		if (iobuf.in_fd >= 0 && iobuf.in.size - iobuf.in.len) {
			if (!read_batch || batch_fd >= 0) {
				FD_SET(iobuf.in_fd, &r_fds);
				FD_SET(iobuf.in_fd, &e_fds);
			}
			if (iobuf.in_fd > max_fd)
				max_fd = iobuf.in_fd;
		}

		/* Only do more filesfrom processing if there is enough room in the out buffer. */
		if (ff_forward_fd >= 0 && iobuf.out.size - iobuf.out.len > FILESFROM_BUFLEN*2) {
			FD_SET(ff_forward_fd, &r_fds);
			if (ff_forward_fd > max_fd)
				max_fd = ff_forward_fd;
		}

		FD_ZERO(&w_fds);
		if (iobuf.out_fd >= 0) {
			if (iobuf.raw_flushing_ends_before
			 || (!iobuf.msg.len && iobuf.out.len > iobuf.out_empty_len && !(flags & PIO_NEED_MSGROOM))) {
				if (OUT_MULTIPLEXED && !iobuf.raw_flushing_ends_before) {
					/* The iobuf.raw_flushing_ends_before value can point off the end
					 * of the iobuf.out buffer for a while, for easier subtracting. */
					iobuf.raw_flushing_ends_before = iobuf.out.pos + iobuf.out.len;

					SIVAL(iobuf.out.buf + iobuf.raw_data_header_pos, 0,
					      ((MPLEX_BASE + (int)MSG_DATA)<<24) + iobuf.out.len - 4);

					if (msgs2stderr && DEBUG_GTE(IO, 1)) {
						rprintf(FINFO, "[%s] send_msg(%d, %ld)\n",
							who_am_i(), (int)MSG_DATA, (long)iobuf.out.len - 4);
					}

					/* reserve room for the next MSG_DATA header */
					iobuf.raw_data_header_pos = iobuf.raw_flushing_ends_before;
					if (iobuf.raw_data_header_pos >= iobuf.out.size)
						iobuf.raw_data_header_pos -= iobuf.out.size;
					else if (iobuf.raw_data_header_pos + 4 > iobuf.out.size) {
						/* The 4-byte header won't fit at the end of the buffer,
						 * so we'll temporarily reduce the output buffer's size
						 * and put the header at the start of the buffer. */
						reduce_iobuf_size(&iobuf.out, iobuf.raw_data_header_pos);
						iobuf.raw_data_header_pos = 0;
					}
					/* Yes, it is possible for this to make len > size for a while. */
					iobuf.out.len += 4;
				}

				empty_buf_len = iobuf.out_empty_len;
				out = &iobuf.out;
			} else if (iobuf.msg.len) {
				empty_buf_len = 0;
				out = &iobuf.msg;
			} else
				out = NULL;
			if (out) {
				FD_SET(iobuf.out_fd, &w_fds);
				if (iobuf.out_fd > max_fd)
					max_fd = iobuf.out_fd;
			}
		} else
			out = NULL;

		if (max_fd < 0) {
			switch (flags & PIO_NEED_FLAGS) {
			case PIO_NEED_INPUT:
				iobuf.in.len = 0;
				if (kluge_around_eof == 2)
					exit_cleanup(0);
				if (iobuf.in_fd == -2)
					whine_about_eof(True);
				rprintf(FERROR, "error in perform_io: no fd for input.\n");
				exit_cleanup(RERR_PROTOCOL);
			case PIO_NEED_OUTROOM:
			case PIO_NEED_MSGROOM:
				msgs2stderr = 1;
				drain_multiplex_messages();
				if (iobuf.out_fd == -2)
					whine_about_eof(True);
				rprintf(FERROR, "error in perform_io: no fd for output.\n");
				exit_cleanup(RERR_PROTOCOL);
			default:
				/* No stated needs, so I guess this is OK. */
				break;
			}
			break;
		}

		if (got_kill_signal > 0)
			handle_kill_signal(True);

		if (extra_flist_sending_enabled) {
			if (file_total - file_old_total < MAX_FILECNT_LOOKAHEAD && IN_MULTIPLEXED_AND_READY)
				tv.tv_sec = 0;
			else {
				extra_flist_sending_enabled = False;
				tv.tv_sec = select_timeout;
			}
		} else
			tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		cnt = select(max_fd + 1, &r_fds, &w_fds, &e_fds, &tv);

		if (cnt <= 0) {
			if (cnt < 0 && errno == EBADF) {
				msgs2stderr = 1;
				exit_cleanup(RERR_SOCKETIO);
			}
			if (extra_flist_sending_enabled) {
				extra_flist_sending_enabled = False;
				send_extra_file_list(sock_f_out, -1);
				extra_flist_sending_enabled = !flist_eof;
			} else
				check_timeout((flags & PIO_NEED_INPUT) != 0);
			FD_ZERO(&r_fds); /* Just in case... */
			FD_ZERO(&w_fds);
		}

		if (iobuf.in_fd >= 0 && FD_ISSET(iobuf.in_fd, &r_fds)) {
			size_t len, pos = iobuf.in.pos + iobuf.in.len;
			int n;
			if (pos >= iobuf.in.size) {
				pos -= iobuf.in.size;
				len = iobuf.in.size - iobuf.in.len;
			} else
				len = iobuf.in.size - pos;
			if ((n = read(iobuf.in_fd, iobuf.in.buf + pos, len)) <= 0) {
				if (n == 0) {
					/* Signal that input has become invalid. */
					if (!read_batch || batch_fd < 0 || am_generator)
						iobuf.in_fd = -2;
					batch_fd = -1;
					continue;
				}
				if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
					n = 0;
				else {
					/* Don't write errors on a dead socket. */
					if (iobuf.in_fd == sock_f_in) {
						if (am_sender)
							msgs2stderr = 1;
						rsyserr(FERROR_SOCKET, errno, "read error");
					} else
						rsyserr(FERROR, errno, "read error");
					exit_cleanup(RERR_SOCKETIO);
				}
			}
			if (msgs2stderr && DEBUG_GTE(IO, 2))
				rprintf(FINFO, "[%s] recv=%ld\n", who_am_i(), (long)n);

			if (io_timeout) {
				last_io_in = time(NULL);
				if (flags & PIO_NEED_INPUT)
					maybe_send_keepalive(last_io_in, 0);
			}
			stats.total_read += n;

			iobuf.in.len += n;
		}

		if (out && FD_ISSET(iobuf.out_fd, &w_fds)) {
			size_t len = iobuf.raw_flushing_ends_before ? iobuf.raw_flushing_ends_before - out->pos : out->len;
			int n;

			if (bwlimit_writemax && len > bwlimit_writemax)
				len = bwlimit_writemax;

			if (out->pos + len > out->size)
				len = out->size - out->pos;
			if ((n = write(iobuf.out_fd, out->buf + out->pos, len)) <= 0) {
				if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
					n = 0;
				else {
					/* Don't write errors on a dead socket. */
					msgs2stderr = 1;
					iobuf.out_fd = -2;
					iobuf.out.len = iobuf.msg.len = iobuf.raw_flushing_ends_before = 0;
					rsyserr(FERROR_SOCKET, errno, "[%s] write error", who_am_i());
					drain_multiplex_messages();
					exit_cleanup(RERR_SOCKETIO);
				}
			}
			if (msgs2stderr && DEBUG_GTE(IO, 2)) {
				rprintf(FINFO, "[%s] %s sent=%ld\n",
					who_am_i(), out == &iobuf.out ? "out" : "msg", (long)n);
			}

			if (io_timeout)
				last_io_out = time(NULL);
			stats.total_written += n;

			if (bwlimit_writemax)
				sleep_for_bwlimit(n);

			if ((out->pos += n) == out->size) {
				if (iobuf.raw_flushing_ends_before)
					iobuf.raw_flushing_ends_before -= out->size;
				out->pos = 0;
				restore_iobuf_size(out);
			} else if (out->pos == iobuf.raw_flushing_ends_before)
				iobuf.raw_flushing_ends_before = 0;
			if ((out->len -= n) == empty_buf_len) {
				out->pos = 0;
				restore_iobuf_size(out);
				if (empty_buf_len)
					iobuf.raw_data_header_pos = 0;
			}
		}

		if (got_kill_signal > 0)
			handle_kill_signal(True);

		/* We need to help prevent deadlock by doing what reading
		 * we can whenever we are here trying to write. */
		if (IN_MULTIPLEXED_AND_READY && !(flags & PIO_NEED_INPUT)) {
			while (!iobuf.raw_input_ends_before && iobuf.in.len > 512)
				read_a_msg();
			if (flist_receiving_enabled && iobuf.in.len > 512)
				wait_for_receiver(); /* generator only */
		}

		if (ff_forward_fd >= 0 && FD_ISSET(ff_forward_fd, &r_fds)) {
			/* This can potentially flush all output and enable
			 * multiplexed output, so keep this last in the loop
			 * and be sure to not cache anything that would break
			 * such a change. */
			forward_filesfrom_data();
		}
	}
  double_break:

	if (got_kill_signal > 0)
		handle_kill_signal(True);

	data = iobuf.in.buf + iobuf.in.pos;

	if (flags & PIO_CONSUME_INPUT) {
		iobuf.in.len -= needed;
		iobuf.in.pos += needed;
		if (iobuf.in.pos == iobuf.raw_input_ends_before)
			iobuf.raw_input_ends_before = 0;
		if (iobuf.in.pos >= iobuf.in.size) {
			iobuf.in.pos -= iobuf.in.size;
			if (iobuf.raw_input_ends_before)
				iobuf.raw_input_ends_before -= iobuf.in.size;
		}
	}

	return data;
}

static void raw_read_buf(char *buf, size_t len)
{
	size_t pos = iobuf.in.pos;
	char *data = perform_io(len, PIO_INPUT_AND_CONSUME);
	if (iobuf.in.pos <= pos && len) {
		size_t siz = len - iobuf.in.pos;
		memcpy(buf, data, siz);
		memcpy(buf + siz, iobuf.in.buf, iobuf.in.pos);
	} else
		memcpy(buf, data, len);
}

static int32 raw_read_int(void)
{
	char *data, buf[4];
	if (iobuf.in.size - iobuf.in.pos >= 4)
		data = perform_io(4, PIO_INPUT_AND_CONSUME);
	else
		raw_read_buf(data = buf, 4);
	return IVAL(data, 0);
}

void noop_io_until_death(void)
{
	char buf[1024];

	if (!iobuf.in.buf || !iobuf.out.buf || iobuf.in_fd < 0 || iobuf.out_fd < 0 || kluge_around_eof)
		return;

	kluge_around_eof = 2;
	/* Setting an I/O timeout ensures that if something inexplicably weird
	 * happens, we won't hang around forever. */
	if (!io_timeout)
		set_io_timeout(60);

	while (1)
		read_buf(iobuf.in_fd, buf, sizeof buf);
}

/* Buffer a message for the multiplexed output stream.  Is not used for (normal) MSG_DATA. */
int send_msg(enum msgcode code, const char *buf, size_t len, int convert)
{
	char *hdr;
	size_t needed, pos;
	BOOL want_debug = DEBUG_GTE(IO, 1) && convert >= 0 && (msgs2stderr || code != MSG_INFO);

	if (!OUT_MULTIPLEXED)
		return 0;

	if (want_debug)
		rprintf(FINFO, "[%s] send_msg(%d, %ld)\n", who_am_i(), (int)code, (long)len);

	/* When checking for enough free space for this message, we need to
	 * make sure that there is space for the 4-byte header, plus we'll
	 * assume that we may waste up to 3 bytes (if the header doesn't fit
	 * at the physical end of the buffer). */
#ifdef ICONV_OPTION
	if (convert > 0 && ic_send == (iconv_t)-1)
		convert = 0;
	if (convert > 0) {
		/* Ensuring double-size room leaves space for maximal conversion expansion. */
		needed = len*2 + 4 + 3;
	} else
#endif
		needed = len + 4 + 3;
	if (iobuf.msg.len + needed > iobuf.msg.size)
		perform_io(needed, PIO_NEED_MSGROOM);

	pos = iobuf.msg.pos + iobuf.msg.len; /* Must be set after any flushing. */
	if (pos >= iobuf.msg.size)
		pos -= iobuf.msg.size;
	else if (pos + 4 > iobuf.msg.size) {
		/* The 4-byte header won't fit at the end of the buffer,
		 * so we'll temporarily reduce the message buffer's size
		 * and put the header at the start of the buffer. */
		reduce_iobuf_size(&iobuf.msg, pos);
		pos = 0;
	}
	hdr = iobuf.msg.buf + pos;

	iobuf.msg.len += 4; /* Allocate room for the coming header bytes. */

#ifdef ICONV_OPTION
	if (convert > 0) {
		xbuf inbuf;

		INIT_XBUF(inbuf, (char*)buf, len, (size_t)-1);

		len = iobuf.msg.len;
		iconvbufs(ic_send, &inbuf, &iobuf.msg,
			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE | ICB_CIRCULAR_OUT | ICB_INIT);
		if (inbuf.len > 0) {
			rprintf(FERROR, "overflowed iobuf.msg buffer in send_msg");
			exit_cleanup(RERR_UNSUPPORTED);
		}
		len = iobuf.msg.len - len;
	} else
#endif
	{
		size_t siz;

		if ((pos += 4) == iobuf.msg.size)
			pos = 0;

		/* Handle a split copy if we wrap around the end of the circular buffer. */
		if (pos >= iobuf.msg.pos && (siz = iobuf.msg.size - pos) < len) {
			memcpy(iobuf.msg.buf + pos, buf, siz);
			memcpy(iobuf.msg.buf, buf + siz, len - siz);
		} else
			memcpy(iobuf.msg.buf + pos, buf, len);

		iobuf.msg.len += len;
	}

	SIVAL(hdr, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	if (want_debug && convert > 0)
		rprintf(FINFO, "[%s] converted msg len=%ld\n", who_am_i(), (long)len);

	return 1;
}

void send_msg_int(enum msgcode code, int num)
{
	char numbuf[4];

	if (DEBUG_GTE(IO, 1))
		rprintf(FINFO, "[%s] send_msg_int(%d, %d)\n", who_am_i(), (int)code, num);

	SIVAL(numbuf, 0, num);
	send_msg(code, numbuf, 4, -1);
}

static void got_flist_entry_status(enum festatus status, int ndx)
{
	struct file_list *flist = flist_for_ndx(ndx, "got_flist_entry_status");

	if (remove_source_files) {
		active_filecnt--;
		active_bytecnt -= F_LENGTH(flist->files[ndx - flist->ndx_start]);
	}

 * @todo Perhaps we want some simple stack functionality, but there's
 * no need to overdo it.
 **/
const char *io_write_phase = phase_unknown;
const char *io_read_phase = phase_unknown;

/** Ignore EOF errors while reading a module listing if the remote
    version is 24 or less. */
int kludge_around_eof = False;

int msg_fd_in = -1;
int msg_fd_out = -1;

static int io_multiplexing_out;
static int io_multiplexing_in;
static int sock_f_in = -1;
static int sock_f_out = -1;
static time_t last_io;
static int no_flush;

static int write_batch_monitor_in = -1;
static int write_batch_monitor_out = -1;

static int io_filesfrom_f_in = -1;
static int io_filesfrom_f_out = -1;
static char io_filesfrom_buf[2048];
static char *io_filesfrom_bp;
static char io_filesfrom_lastchar;
static int io_filesfrom_buflen;

static void read_loop(int fd, char *buf, size_t len);

struct redo_list {
	struct redo_list *next;
	int num;
};

static struct redo_list *redo_list_head;
static struct redo_list *redo_list_tail;

struct msg_list {
	struct msg_list *next;
	char *buf;
	int len;
};

static struct msg_list *msg_list_head;
static struct msg_list *msg_list_tail;

static void redo_list_add(int num)
{
	struct redo_list *rl;

	if (!(rl = new(struct redo_list)))
		exit_cleanup(RERR_MALLOC);
	rl->next = NULL;
	rl->num = num;
	if (redo_list_tail)
		redo_list_tail->next = rl;
	else
		redo_list_head = rl;
	redo_list_tail = rl;
}

static void check_timeout(void)
{
	time_t t;

	if (!io_timeout)
		return;

	if (!last_io) {
		last_io = time(NULL);
		return;
	}

	t = time(NULL);

	if (t - last_io >= io_timeout) {
		if (!am_server && !am_daemon) {
			rprintf(FERROR, "io timeout after %d seconds - exiting\n",
				(int)(t-last_io));
		}
		exit_cleanup(RERR_TIMEOUT);
	}
}


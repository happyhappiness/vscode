#define HEADERLEN	65536
#endif

typedef void SIGHDLR(int sig);

/* Local functions */
static int client_comm_bind(int, const IpAddress &);

static int client_comm_connect(int, const IpAddress &, struct timeval *);
static void usage(const char *progname);

static int Now(struct timeval *);
static SIGHDLR catchSignal;
static SIGHDLR pipe_handler;
static void set_our_signal(void);
static ssize_t myread(int fd, void *buf, size_t len);
static ssize_t mywrite(int fd, void *buf, size_t len);
static int put_fd;
static char *put_file = NULL;

static struct stat sb;
int total_bytes = 0;
int io_timeout = 120;

#ifdef _SQUID_MSWIN_
void
Win32SockCleanup(void)
{
    WSACleanup();
    return;
}
#endif /* ifdef _SQUID_MSWIN_ */

static void
usage(const char *progname)
{
    fprintf(stderr,
            "Version: %s\n"
            "Usage: %s [-arsv] [-A 'string'] [-g count] [-h remote host] [-H 'string'] [-i IMS] [-I ping-interval] [-j 'Host-header']"
            "[-k] [-l local-host] [-m method] [-p port] [-P file] [-t count] [-T timeout] [-u proxy-user] [-U www-user] "
            "[-V version] [-w proxy-password] [-W www-password] url\n"
            "\n"
            "Options:\n"
            "    -a           Do NOT include Accept: header.\n"
            "    -A           User-Agent: header. Use \"\" to omit.\n"
            "    -g count     Ping mode, perform \"count\" iterations (0 to loop until interrupted).\n"

#define HEADERLEN	65536
#endif

typedef void SIGHDLR(int sig);

/* Local functions */
static int client_comm_bind(int, const Ip::Address &);

static int client_comm_connect(int, const Ip::Address &, struct timeval *);
static void usage(const char *progname);

static int Now(struct timeval *);
SIGHDLR catchSignal;
SIGHDLR pipe_handler;
static void set_our_signal(void);
static ssize_t myread(int fd, void *buf, size_t len);
static ssize_t mywrite(int fd, void *buf, size_t len);


#if HAVE_GSSAPI
static int check_gss_err(OM_uint32 major_status, OM_uint32 minor_status, const char *function);
static char *GSSAPI_token(const char *server);
#endif

static int put_fd;
static char *put_file = NULL;

static struct stat sb;
int total_bytes = 0;
int io_timeout = 120;

#if _SQUID_WINDOWS_
void
Win32SockCleanup(void)
{
    WSACleanup();
    return;
}
#endif

static void
usage(const char *progname)
{
    fprintf(stderr,
            "Version: %s\n"
            "Usage: %s [-arsv] [-A 'string'] [-g count] [-h remote host] [-H 'string'] [-i IMS] [-I ping-interval] [-j 'Host-header']"
            "[-k] [-l local-host] [-m method] "
#if HAVE_GSSAPI
            "[-n] [-N] "
#endif
            "[-p port] [-P file] [-t count] [-T timeout] [-u proxy-user] [-U www-user] "
            "[-V version] [-w proxy-password] [-W www-password] url\n"
            "\n"
            "Options:\n"
            "    -a           Do NOT include Accept: header.\n"
            "    -A           User-Agent: header. Use \"\" to omit.\n"
            "    -g count     Ping mode, perform \"count\" iterations (0 to loop until interrupted).\n"

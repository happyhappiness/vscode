#ifdef ICONV_OPTION
char *iconv_opt = ICONV_OPTION;
#endif

struct chmod_mode_struct *chmod_modes = NULL;

static int daemon_opt;   /* sets am_daemon after option error-reporting */
static int omit_dir_times = 0;
static int F_option_cnt = 0;
static int modify_window_set;
static int itemize_changes = 0;
static int refused_delete, refused_archive_part, refused_compress;
static int refused_partial, refused_progress, refused_delete_before;
static int refused_delete_during;
static int refused_inplace, refused_no_iconv;
static char *max_size_arg, *min_size_arg;
static char tmp_partialdir[] = ".~tmp~";

/** Local address to bind.  As a character string because it's
 * interpreted by the IPv6 layer: should be a numeric IP4 or IP6
 * address, or a hostname. **/
char *bind_address;


static void print_rsync_version(enum logcode f)
{
	char *subprotocol = "";
	char const *got_socketpair = "no ";
	char const *have_inplace = "no ";
	char const *hardlinks = "no ";
	char const *symtimes = "no ";
	char const *acls = "no ";
	char const *xattrs = "no ";
	char const *links = "no ";
	char const *iconv = "no ";
	char const *ipv6 = "no ";

#define ERR_SYNTAX 2
#define ERR_PWMISMATCH 3
#define ERR_INTERRUPTED 4
#define ERR_OVERFLOW 5
#define ERR_BADUSER 6

#define APHTP_NEWFILE        1
#define APHTP_NOFILE         2
#define APHTP_NONINTERACTIVE 4

apr_file_t *errfile;
apr_file_t *ftemp = NULL;

static void to64(char *s, unsigned long v, int n)
{
    static unsigned char itoa64[] =         /* 0 ... 63 => ASCII - 64 */
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    while (--n >= 0) {
	*s++ = itoa64[v&0x3f];
	v >>= 6;
    }
}

static void putline(apr_file_t *f, const char *l)
{
    apr_file_puts(l, f);
}

/*
 * Make a password record from the given information.  A zero return
 * indicates success; failure means that the output buffer contains an
 * error message instead.
 */
static int mkrecord(char *user, char *record, size_t rlen, char *passwd,

#define ERR_SYNTAX 2
#define ERR_PWMISMATCH 3
#define ERR_INTERRUPTED 4
#define ERR_OVERFLOW 5
#define ERR_BADUSER 6

/*
 * This needs to be declared statically so the signal handler can
 * access it.
 */
static char *tempfilename;
/*
 * If our platform knows about the tmpnam() external buffer size, create
 * a buffer to pass in.  This is needed in a threaded environment, or
 * one that thinks it is (like HP-UX).
 */
#ifdef L_tmpnam
static char tname_buf[L_tmpnam];
#else
static char *tname_buf = NULL;
#endif

/*
 * Get a line of input from the user, not including any terminating
 * newline.
 */
static int getline(char *s, int n, FILE *f)
{
    register int i = 0;

    while (1) {
	s[i] = (char) fgetc(f);

	if (s[i] == CR) {
	    s[i] = fgetc(f);
	}

	if ((s[i] == 0x4) || (s[i] == LF) || (i == (n - 1))) {
	    s[i] = '\0';
	    return (feof(f) ? 1 : 0);
	}
	++i;
    }
}

static void putline(FILE *f, char *l)
{
    int x;

    for (x = 0; l[x]; x++) {
	fputc(l[x], f);
    }
    fputc('\n', f);
}

static void to64(char *s, unsigned long v, int n)
{
    static unsigned char itoa64[] =         /* 0 ... 63 => ASCII - 64 */
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    while (--n >= 0) {
	*s++ = itoa64[v&0x3f];
	v >>= 6;
    }
}

/*
 * Make a password record from the given information.  A zero return
 * indicates success; failure means that the output buffer contains an
 * error message instead.
 */
static int mkrecord(char *user, char *record, size_t rlen, char *passwd,

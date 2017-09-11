
/*
 * This buffer is rather large for stack allocation, so use a single buffer for
 * all profile dumps.
 */
static malloc_mutex_t	prof_dump_mtx;
static char		prof_dump_buf[
    /* Minimize memory bloat for non-prof builds. */
#ifdef JEMALLOC_PROF
    PROF_DUMP_BUFSIZE
#else
    1
#endif
];
static unsigned		prof_dump_buf_end;
static int		prof_dump_fd;

/* Do not dump any profiles until bootstrapping is complete. */
static bool		prof_booted = false;

/******************************************************************************/

void
bt_init(prof_bt_t *bt, void **vec)

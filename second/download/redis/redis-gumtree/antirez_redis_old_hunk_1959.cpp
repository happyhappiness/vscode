
/*
 * This buffer is rather large for stack allocation, so use a single buffer for
 * all profile dumps.  The buffer is implicitly protected by bt2ctx_mtx, since
 * it must be locked anyway during dumping.
 */
static char		prof_dump_buf[PROF_DUMP_BUFSIZE];
static unsigned		prof_dump_buf_end;
static int		prof_dump_fd;

/* Do not dump any profiles until bootstrapping is complete. */
static bool		prof_booted = false;

/******************************************************************************/
/* Function prototypes for non-inline static functions. */

static prof_bt_t	*bt_dup(prof_bt_t *bt);
static void	bt_destroy(prof_bt_t *bt);
#ifdef JEMALLOC_PROF_LIBGCC
static _Unwind_Reason_Code	prof_unwind_init_callback(
    struct _Unwind_Context *context, void *arg);
static _Unwind_Reason_Code	prof_unwind_callback(
    struct _Unwind_Context *context, void *arg);
#endif
static bool	prof_flush(bool propagate_err);
static bool	prof_write(bool propagate_err, const char *s);
static bool	prof_printf(bool propagate_err, const char *format, ...)
    JEMALLOC_ATTR(format(printf, 2, 3));
static void	prof_ctx_sum(prof_ctx_t *ctx, prof_cnt_t *cnt_all,
    size_t *leak_nctx);
static void	prof_ctx_destroy(prof_ctx_t *ctx);
static void	prof_ctx_merge(prof_ctx_t *ctx, prof_thr_cnt_t *cnt);
static bool	prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx,
    prof_bt_t *bt);
static bool	prof_dump_maps(bool propagate_err);
static bool	prof_dump(bool propagate_err, const char *filename,
    bool leakcheck);
static void	prof_dump_filename(char *filename, char v, int64_t vseq);
static void	prof_fdump(void);
static void	prof_bt_hash(const void *key, unsigned minbits, size_t *hash1,
    size_t *hash2);
static bool	prof_bt_keycomp(const void *k1, const void *k2);
static malloc_mutex_t	*prof_ctx_mutex_choose(void);

/******************************************************************************/

void
bt_init(prof_bt_t *bt, void **vec)

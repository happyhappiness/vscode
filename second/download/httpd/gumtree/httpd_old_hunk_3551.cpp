        }
        if (!unsolicited && !ufrag) {
            ufrag = 1;
        }
        apr_file_printf(errfile, "unsolicited size %d.%d%c" APR_EOL_STR,
                        (int)(unsolicited), (int)(ufrag), utype);
     }
     apr_file_printf(errfile, "size limit %d.0%c" APR_EOL_STR,
                     (int)(s->max), mtype);
     apr_file_printf(errfile, "total size was %d.%d%c, total size now "
                              "%d.%d%c" APR_EOL_STR,
                     (int)(s->total), (int)(tfrag), ttype,
                     (int)(s->sum), (int)(sfrag), stype);
     apr_file_printf(errfile, "total entries was %d, total entries now %d"
                              APR_EOL_STR, (int)(s->etotal),
                              (int)(s->entries));
     apr_file_printf(errfile, "%d entries deleted (%d from future, %d "
                              "expired, %d fresh)" APR_EOL_STR,
                     (int)(s->etotal - s->entries), (int)(s->dfuture),
                     (int)(s->dexpired), (int)(s->dfresh));
}

/*
 * delete a single file
 */
static void delete_file(char *path, char *basename, apr_pool_t *pool)
{
    char *nextpath;
    apr_pool_t *p;

    if (dryrun) {
        return;
    }

    /* temp pool, otherwise lots of memory could be allocated */
    apr_pool_create(&p, pool);
    nextpath = apr_pstrcat(p, path, "/", basename, NULL);
    apr_file_remove(nextpath, p);
    apr_pool_destroy(p);

    if (benice) {
        if (++delcount >= DELETE_NICE) {
            apr_sleep(NICE_DELAY);
            delcount = 0;
        }
    }
}

/*
 * delete cache file set
 */
static void delete_entry(char *path, char *basename, apr_pool_t *pool)
{
    char *nextpath;
    apr_pool_t *p;

    if (dryrun) {
        return;
    }

    /* temp pool, otherwise lots of memory could be allocated */
    apr_pool_create(&p, pool);

    nextpath = apr_pstrcat(p, path, "/", basename, CACHE_HEADER_SUFFIX, NULL);
    apr_file_remove(nextpath, p);

    nextpath = apr_pstrcat(p, path, "/", basename, CACHE_DATA_SUFFIX, NULL);
    apr_file_remove(nextpath, p);

    apr_pool_destroy(p);

    if (benice) {
        delcount += 2;
        if (delcount >= DELETE_NICE) {
            apr_sleep(NICE_DELAY);
            delcount = 0;
        }
    }
}

/*
 * walk the cache directory tree
 */
static int process_dir(char *path, apr_pool_t *pool)
{
    apr_dir_t *dir;
    apr_pool_t *p;
    apr_hash_t *h;
    apr_hash_index_t *i;
    apr_file_t *fd;
    apr_status_t status;
    apr_finfo_t info;
    apr_size_t len;
    apr_time_t current, deviation;
    char *nextpath, *base, *ext, *orig_basename;
    APR_RING_ENTRY(_direntry) anchor;
    DIRENTRY *d, *t, *n;
    ENTRY *e;
    int skip, retries;
    disk_cache_info_t disk_info;

    APR_RING_INIT(&anchor, _direntry, link);
    apr_pool_create(&p, pool);
    h = apr_hash_make(p);
    fd = NULL;
    skip = 0;
    deviation = MAXDEVIATION * APR_USEC_PER_SEC;

    if (apr_dir_open(&dir, path, p) != APR_SUCCESS) {
        return 1;
    }


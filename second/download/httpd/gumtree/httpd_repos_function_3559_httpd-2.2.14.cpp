static void fill_out_finfo(apr_finfo_t *finfo, struct_stat *info,
                           apr_int32_t wanted)
{ 
    finfo->valid = APR_FINFO_MIN | APR_FINFO_IDENT | APR_FINFO_NLINK
                 | APR_FINFO_OWNER | APR_FINFO_PROT;
    finfo->protection = apr_unix_mode2perms(info->st_mode);
    finfo->filetype = filetype_from_mode(info->st_mode);
    finfo->user = info->st_uid;
    finfo->group = info->st_gid;
    finfo->size = info->st_size;
    finfo->device = info->st_dev;
    finfo->nlink = info->st_nlink;

    /* Check for overflow if storing a 64-bit st_ino in a 32-bit
     * apr_ino_t for LFS builds: */
    if (sizeof(apr_ino_t) >= sizeof(info->st_ino)
        || (apr_ino_t)info->st_ino == info->st_ino) {
        finfo->inode = info->st_ino;
    } else {
        finfo->valid &= ~APR_FINFO_INODE;
    }

    apr_time_ansi_put(&finfo->atime, info->st_atime);
#ifdef HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC
    finfo->atime += info->st_atim.tv_nsec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_ATIMENSEC)
    finfo->atime += info->st_atimensec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_ATIME_N)
    finfo->ctime += info->st_atime_n / APR_TIME_C(1000);
#endif

    apr_time_ansi_put(&finfo->mtime, info->st_mtime);
#ifdef HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
    finfo->mtime += info->st_mtim.tv_nsec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_MTIMENSEC)
    finfo->mtime += info->st_mtimensec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_MTIME_N)
    finfo->ctime += info->st_mtime_n / APR_TIME_C(1000);
#endif

    apr_time_ansi_put(&finfo->ctime, info->st_ctime);
#ifdef HAVE_STRUCT_STAT_ST_CTIM_TV_NSEC
    finfo->ctime += info->st_ctim.tv_nsec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_CTIMENSEC)
    finfo->ctime += info->st_ctimensec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_CTIME_N)
    finfo->ctime += info->st_ctime_n / APR_TIME_C(1000);
#endif

#ifdef HAVE_STRUCT_STAT_ST_BLOCKS
#ifdef DEV_BSIZE
    finfo->csize = (apr_off_t)info->st_blocks * (apr_off_t)DEV_BSIZE;
#else
    finfo->csize = (apr_off_t)info->st_blocks * (apr_off_t)512;
#endif
    finfo->valid |= APR_FINFO_CSIZE;
#endif
}
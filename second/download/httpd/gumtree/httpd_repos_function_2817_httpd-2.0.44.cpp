static void fill_out_finfo(apr_finfo_t *finfo, struct stat *info,
                           apr_int32_t wanted)
{ 
    finfo->valid = APR_FINFO_MIN | APR_FINFO_IDENT | APR_FINFO_NLINK;
    finfo->protection = apr_unix_mode2perms(info->st_mode);
    finfo->filetype = filetype_from_mode(info->st_mode);
    finfo->user = info->st_uid;
    finfo->group = info->st_gid;
    finfo->size = info->st_size;
    finfo->inode = info->st_ino;
    finfo->device = info->st_dev;
    finfo->nlink = info->st_nlink;
    apr_time_ansi_put(&finfo->atime, info->st_atime.tv_sec);
    apr_time_ansi_put(&finfo->mtime, info->st_mtime.tv_sec);
    apr_time_ansi_put(&finfo->ctime, info->st_ctime.tv_sec);
    /* ### needs to be revisited  
     * if (wanted & APR_FINFO_CSIZE) {
     *   finfo->csize = info->st_blocks * 512;
     *   finfo->valid |= APR_FINFO_CSIZE;
     * }
     */
}
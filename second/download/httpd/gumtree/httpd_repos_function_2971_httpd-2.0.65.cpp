static void fill_out_finfo(apr_finfo_t *finfo, struct stat *info,
                           apr_int32_t wanted)
{ 
    finfo->valid = APR_FINFO_MIN | APR_FINFO_IDENT | APR_FINFO_NLINK
                 | APR_FINFO_OWNER | APR_FINFO_PROT;
    finfo->protection = apr_unix_mode2perms(info->st_mode);
    finfo->filetype = filetype_from_mode(info->st_mode);
    finfo->user = info->st_uid;
    finfo->group = info->st_gid;
    finfo->size = info->st_size;
    finfo->inode = info->st_ino;
    finfo->device = info->st_dev;
    finfo->nlink = info->st_nlink;
    apr_time_ansi_put(&finfo->atime, info->st_atime);
    apr_time_ansi_put(&finfo->mtime, info->st_mtime);
    apr_time_ansi_put(&finfo->ctime, info->st_ctime);
    /* ### needs to be revisited  
     * if (wanted & APR_FINFO_CSIZE) {
     *   finfo->csize = info->st_blocks * 512;
     *   finfo->valid |= APR_FINFO_CSIZE;
     * }
     */
}
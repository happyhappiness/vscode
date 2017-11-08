static void FS3_to_finfo(apr_finfo_t *finfo, FILESTATUS3 *fstatus)
{
    finfo->protection = (fstatus->attrFile & FILE_READONLY) ? 0x555 : 0x777;

    if (fstatus->attrFile & FILE_DIRECTORY)
        finfo->filetype = APR_DIR;
    else
        finfo->filetype = APR_REG;

    finfo->user = 0;
    finfo->group = 0;
    finfo->inode = 0;
    finfo->device = 0;
    finfo->size = fstatus->cbFile;
    finfo->csize = fstatus->cbFileAlloc;
    apr_os2_time_to_apr_time(&finfo->atime, fstatus->fdateLastAccess, 
                             fstatus->ftimeLastAccess );
    apr_os2_time_to_apr_time(&finfo->mtime, fstatus->fdateLastWrite,  
                             fstatus->ftimeLastWrite );
    apr_os2_time_to_apr_time(&finfo->ctime, fstatus->fdateCreation,   
                             fstatus->ftimeCreation );
    finfo->valid = APR_FINFO_TYPE | APR_FINFO_PROT | APR_FINFO_SIZE
                 | APR_FINFO_CSIZE | APR_FINFO_MTIME 
                 | APR_FINFO_CTIME | APR_FINFO_ATIME;
}
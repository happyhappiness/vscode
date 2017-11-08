static apr_status_t handle_type(apr_filetype_e *ftype, HFILE file)
{
    ULONG filetype, fileattr, rc;

    rc = DosQueryHType(file, &filetype, &fileattr);

    if (rc == 0) {
        switch (filetype & 0xff) {
        case 0:
            *ftype = APR_REG;
            break;

        case 1:
            *ftype = APR_CHR;
            break;

        case 2:
            *ftype = APR_PIPE;
            break;

        default:
            /* Brian, is this correct???
             */
            *ftype = APR_UNKFILE;
            break;
        }

        return APR_SUCCESS;
    }
    return APR_FROM_OS_ERROR(rc);
}
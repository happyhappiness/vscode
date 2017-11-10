static apr_filetype_e filetype_from_dirent_type(int type)
{
    switch (type) {
    case DT_REG:
        return APR_REG;
    case DT_DIR:
        return APR_DIR;
    case DT_LNK:
        return APR_LNK;
    case DT_CHR:
        return APR_CHR;
    case DT_BLK:
        return APR_BLK;
#if defined(DT_FIFO)
    case DT_FIFO:
        return APR_PIPE;
#endif
#if !defined(BEOS) && defined(DT_SOCK)
    case DT_SOCK:
        return APR_SOCK;
#endif
    default:
        return APR_UNKFILE;
    }
}
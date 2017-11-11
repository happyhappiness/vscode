static apr_fileperms_t convert_prot(ACCESS_MASK acc, prot_scope_e scope)
{
    /* These choices are based on the single filesystem bit that controls
     * the given behavior.  They are -not- recommended for any set protection
     * function, such a function should -set- use GENERIC_READ/WRITE/EXECUTE
     */
    apr_fileperms_t prot = 0;
    if (acc & FILE_EXECUTE)
        prot |= APR_WEXECUTE;
    if (acc & FILE_WRITE_DATA)
        prot |= APR_WWRITE;
    if (acc & FILE_READ_DATA)
        prot |= APR_WREAD;
    return (prot << scope);
}
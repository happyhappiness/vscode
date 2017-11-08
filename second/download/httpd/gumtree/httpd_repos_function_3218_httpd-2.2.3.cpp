static void guess_protection_bits(apr_finfo_t *finfo)
{
    /* Read, write execute for owner.  In the Win9x environment, any
     * readable file is executable (well, not entirely 100% true, but
     * still looking for some cheap logic that would help us here.)
     * The same holds on NT if a file doesn't have a DACL (e.g., on FAT)
     */
    if (finfo->protection & APR_FREADONLY) {
        finfo->protection |= APR_WREAD | APR_WEXECUTE;
    }
    else {
        finfo->protection |= APR_WREAD | APR_WEXECUTE | APR_WWRITE;
    }
    finfo->protection |= (finfo->protection << prot_scope_group)
                       | (finfo->protection << prot_scope_user);

    finfo->valid |= APR_FINFO_UPROT | APR_FINFO_GPROT | APR_FINFO_WPROT;
}
apr_status_t more_finfo(apr_finfo_t *finfo, const void *ufile, 
                        apr_int32_t wanted, int whatfile)
{
    PSID user = NULL, grp = NULL;
    PACL dacl = NULL;
    apr_status_t rv;

    if (apr_os_level < APR_WIN_NT)
        guess_protection_bits(finfo);
    else if (wanted & (APR_FINFO_PROT | APR_FINFO_OWNER))
    {
        /* On NT this request is incredibly expensive, but accurate.
         * Since the WinNT-only functions below are protected by the
         * (apr_os_level < APR_WIN_NT) case above, we need no extra
         * tests, but remember GetNamedSecurityInfo & GetSecurityInfo
         * are not supported on 9x.
         */
        SECURITY_INFORMATION sinf = 0;
        PSECURITY_DESCRIPTOR pdesc = NULL;
        if (wanted & (APR_FINFO_USER | APR_FINFO_UPROT))
            sinf |= OWNER_SECURITY_INFORMATION;
        if (wanted & (APR_FINFO_GROUP | APR_FINFO_GPROT))
            sinf |= GROUP_SECURITY_INFORMATION;
        if (wanted & APR_FINFO_PROT)
            sinf |= DACL_SECURITY_INFORMATION;
        if (whatfile == MORE_OF_WFSPEC) {
            apr_wchar_t *wfile = (apr_wchar_t*) ufile;
            int fix = 0;
            if (wcsncmp(wfile, L"\\\\?\\", 4) == 0) {
                fix = 4;
                if (wcsncmp(wfile + fix, L"UNC\\", 4) == 0)
                    wfile[6] = L'\\', fix = 6;
            }
            rv = GetNamedSecurityInfoW(wfile + fix, 
                                 SE_FILE_OBJECT, sinf,
                                 ((wanted & APR_FINFO_USER) ? &user : NULL),
                                 ((wanted & APR_FINFO_GROUP) ? &grp : NULL),
                                 ((wanted & APR_FINFO_PROT) ? &dacl : NULL),
                                 NULL, &pdesc);
            if (fix == 6)
                wfile[6] = L'C';
        }
        else if (whatfile == MORE_OF_FSPEC)
            rv = GetNamedSecurityInfoA((char*)ufile, 
                                 SE_FILE_OBJECT, sinf,
                                 ((wanted & APR_FINFO_USER) ? &user : NULL),
                                 ((wanted & APR_FINFO_GROUP) ? &grp : NULL),
                                 ((wanted & APR_FINFO_PROT) ? &dacl : NULL),
                                 NULL, &pdesc);
        else if (whatfile == MORE_OF_HANDLE)
            rv = GetSecurityInfo((HANDLE)ufile, 
                                 SE_FILE_OBJECT, sinf,
                                 ((wanted & APR_FINFO_USER) ? &user : NULL),
                                 ((wanted & APR_FINFO_GROUP) ? &grp : NULL),
                                 ((wanted & APR_FINFO_PROT) ? &dacl : NULL),
                                 NULL, &pdesc);
        else
            return APR_INCOMPLETE;
        if (rv == ERROR_SUCCESS)
            apr_pool_cleanup_register(finfo->pool, pdesc, free_localheap, 
                                 apr_pool_cleanup_null);
        else
            user = grp = dacl = NULL;

        if (user) {
            finfo->user = user;
            finfo->valid |= APR_FINFO_USER;
        }

        if (grp) {
            finfo->group = grp;
            finfo->valid |= APR_FINFO_GROUP;
        }

        if (dacl) {
            /* Retrieved the discresionary access list */
            resolve_prot(finfo, wanted, dacl);
        }
        else if (wanted & APR_FINFO_PROT)
            guess_protection_bits(finfo);
    }

    return ((wanted & ~finfo->valid) ? APR_INCOMPLETE : APR_SUCCESS);
}
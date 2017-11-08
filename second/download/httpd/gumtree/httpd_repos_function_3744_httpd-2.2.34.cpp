apr_status_t more_finfo(apr_finfo_t *finfo, const void *ufile, 
                        apr_int32_t wanted, int whatfile)
{
    PSID user = NULL, grp = NULL;
    PACL dacl = NULL;
    apr_status_t rv;

    if (apr_os_level < APR_WIN_NT)
        return guess_protection_bits(finfo, wanted);

    if (wanted & (APR_FINFO_PROT | APR_FINFO_OWNER))
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
                                 ((wanted & (APR_FINFO_USER | APR_FINFO_UPROT)) ? &user : NULL),
                                 ((wanted & (APR_FINFO_GROUP | APR_FINFO_GPROT)) ? &grp : NULL),
                                 ((wanted & APR_FINFO_PROT) ? &dacl : NULL),
                                 NULL, &pdesc);
            if (fix == 6)
                wfile[6] = L'C';
        }
        else if (whatfile == MORE_OF_FSPEC)
            rv = GetNamedSecurityInfoA((char*)ufile, 
                                 SE_FILE_OBJECT, sinf,
                                 ((wanted & (APR_FINFO_USER | APR_FINFO_UPROT)) ? &user : NULL),
                                 ((wanted & (APR_FINFO_GROUP | APR_FINFO_GPROT)) ? &grp : NULL),
                                 ((wanted & APR_FINFO_PROT) ? &dacl : NULL),
                                 NULL, &pdesc);
        else if (whatfile == MORE_OF_HANDLE)
            rv = GetSecurityInfo((HANDLE)ufile, 
                                 SE_FILE_OBJECT, sinf,
                                 ((wanted & (APR_FINFO_USER | APR_FINFO_UPROT)) ? &user : NULL),
                                 ((wanted & (APR_FINFO_GROUP | APR_FINFO_GPROT)) ? &grp : NULL),
                                 ((wanted & APR_FINFO_PROT) ? &dacl : NULL),
                                 NULL, &pdesc);
        else
            return APR_INCOMPLETE; /* should not occur */
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
            guess_protection_bits(finfo, wanted);
    }

    if ((apr_os_level >= APR_WIN_2000) && (wanted & APR_FINFO_CSIZE)
                                       && (finfo->filetype == APR_REG))
    {
        DWORD sizelo, sizehi;
        if (whatfile == MORE_OF_HANDLE) {
            /* Not available for development and implementation under
             * a reasonable license; if you review the licensing
             * terms and conditions of;
             *   http://go.microsoft.com/fwlink/?linkid=84083
             * you probably understand why APR chooses not to implement.
             */
            IOSB sb;
            FSI fi;
            if ((ZwQueryInformationFile((HANDLE)ufile, &sb, 
                                       &fi, sizeof(fi), 5) == 0) 
                    && (sb.Status == 0)) {
                finfo->csize = fi.AllocationSize;
                finfo->valid |= APR_FINFO_CSIZE;
            }
        }
        else {
            SetLastError(NO_ERROR);
            if (whatfile == MORE_OF_WFSPEC)
                sizelo = GetCompressedFileSizeW((apr_wchar_t*)ufile, &sizehi);
            else if (whatfile == MORE_OF_FSPEC)
                sizelo = GetCompressedFileSizeA((char*)ufile, &sizehi);
            else
                return APR_EGENERAL; /* should not occur */
        
            if (sizelo != INVALID_FILE_SIZE || GetLastError() == NO_ERROR) {
#if APR_HAS_LARGE_FILES
                finfo->csize =  (apr_off_t)sizelo
                             | ((apr_off_t)sizehi << 32);
#else
                finfo->csize = (apr_off_t)sizelo;
                if (finfo->csize < 0 || sizehi)
                    finfo->csize = 0x7fffffff;
#endif
                finfo->valid |= APR_FINFO_CSIZE;
            }
        }
    }
    return ((wanted & ~finfo->valid) ? APR_INCOMPLETE : APR_SUCCESS);
}
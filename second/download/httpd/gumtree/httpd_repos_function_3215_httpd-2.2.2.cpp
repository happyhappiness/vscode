static void resolve_prot(apr_finfo_t *finfo, apr_int32_t wanted, PACL dacl)
{
    TRUSTEE_W ident = {NULL, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_SID};
    ACCESS_MASK acc;
    /*
     * This function is only invoked for WinNT, 
     * there is no reason for os_level testing here.
     */
    if ((wanted & APR_FINFO_WPROT) && !worldid) {
        SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_WORLD_SID_AUTHORITY;
        if (AllocateAndInitializeSid(&SIDAuth, 1, SECURITY_WORLD_RID,
                                     0, 0, 0, 0, 0, 0, 0, &worldid))
            atexit(free_world);
        else
            worldid = NULL;
    }
    if ((wanted & APR_FINFO_UPROT) && (finfo->valid & APR_FINFO_USER)) {
        ident.TrusteeType = TRUSTEE_IS_USER;
        ident.ptstrName = finfo->user;
        /* GetEffectiveRightsFromAcl isn't supported under Win9x,
         * which shouldn't come as a surprize.  Since we are passing
         * TRUSTEE_IS_SID, always skip the A->W layer.
         */
        if (GetEffectiveRightsFromAclW(dacl, &ident, &acc) == ERROR_SUCCESS) {
            finfo->protection |= convert_prot(acc, prot_scope_user);
            finfo->valid |= APR_FINFO_UPROT;
        }
    }
    /* Windows NT: did not return group rights.
     * Windows 2000 returns group rights information.
     * Since WinNT kernels don't follow the unix model of 
     * group associations, this all all pretty mute.
     */
    if ((wanted & APR_FINFO_GPROT) && (finfo->valid & APR_FINFO_GROUP)) {
        ident.TrusteeType = TRUSTEE_IS_GROUP;
        ident.ptstrName = finfo->group;
        if (GetEffectiveRightsFromAclW(dacl, &ident, &acc) == ERROR_SUCCESS) {
            finfo->protection |= convert_prot(acc, prot_scope_group);
            finfo->valid |= APR_FINFO_GPROT;
        }
    }
    if ((wanted & APR_FINFO_WPROT) && (worldid)) {
        ident.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
        ident.ptstrName = worldid;
        if (GetEffectiveRightsFromAclW(dacl, &ident, &acc) == ERROR_SUCCESS) {
            finfo->protection |= convert_prot(acc, prot_scope_world);
            finfo->valid |= APR_FINFO_WPROT;
        }
    }
}
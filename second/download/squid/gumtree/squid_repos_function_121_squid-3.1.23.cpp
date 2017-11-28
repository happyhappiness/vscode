char *
GetDomainName(void)
{
    static char *DomainName = NULL;
    PDSROLE_PRIMARY_DOMAIN_INFO_BASIC pDSRoleInfo;
    DWORD netret;

    if ((netret = DsRoleGetPrimaryDomainInformation(NULL, DsRolePrimaryDomainInfoBasic, (PBYTE *) & pDSRoleInfo) == ERROR_SUCCESS)) {
        /*
         * Check the machine role.
         */

        if ((pDSRoleInfo->MachineRole == DsRole_RoleMemberWorkstation) ||
                (pDSRoleInfo->MachineRole == DsRole_RoleMemberServer) ||
                (pDSRoleInfo->MachineRole == DsRole_RoleBackupDomainController) ||
                (pDSRoleInfo->MachineRole == DsRole_RolePrimaryDomainController)) {

            size_t len = wcslen(pDSRoleInfo->DomainNameFlat);

            /* allocate buffer for str + null termination */
            safe_free(DomainName);
            DomainName = (char *) xmalloc(len + 1);
            if (DomainName == NULL)
                return NULL;

            /* copy unicode buffer */
            WideCharToMultiByte(CP_ACP, 0, pDSRoleInfo->DomainNameFlat, -1, DomainName, len, NULL, NULL);

            /* add null termination */
            DomainName[len] = '\0';

            /*
             * Member of a domain. Display it in debug mode.
             */
            debug("Member of Domain %s\n", DomainName);
            debug("Into forest %S\n", pDSRoleInfo->DomainForestName);

        } else {
            debug("Not a Domain member\n");
        }
    } else
        debug("DsRoleGetPrimaryDomainInformation Error: %ld\n", netret);

    /*
     * Free the allocated memory.
     */
    if (pDSRoleInfo != NULL)
        DsRoleFreeMemory(pDSRoleInfo);

    return DomainName;
}
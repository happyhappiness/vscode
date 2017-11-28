char *
GetDomainName(void)
{
    LSA_HANDLE PolicyHandle;
    LSA_OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS status;
    PPOLICY_PRIMARY_DOMAIN_INFO ppdiDomainInfo;
    PWKSTA_INFO_100 pwkiWorkstationInfo;
    DWORD netret;
    char *DomainName = NULL;

    /*
     * Always initialize the object attributes to all zeroes.
     */
    memset(&ObjectAttributes, '\0', sizeof(ObjectAttributes));

    /*
     * You need the local workstation name. Use NetWkstaGetInfo at level
     * 100 to retrieve a WKSTA_INFO_100 structure.
     *
     * The wki100_computername field contains a pointer to a UNICODE
     * string containing the local computer name.
     */
    netret = NetWkstaGetInfo(NULL, 100, (LPBYTE *) & pwkiWorkstationInfo);
    if (netret == NERR_Success) {
        /*
         * We have the workstation name in:
         * pwkiWorkstationInfo->wki100_computername
         *
         * Next, open the policy object for the local system using
         * the LsaOpenPolicy function.
         */
        status = LsaOpenPolicy(
                     NULL,
                     &ObjectAttributes,
                     GENERIC_READ | POLICY_VIEW_LOCAL_INFORMATION,
                     &PolicyHandle
                 );

        /*
         * Error checking.
         */
        if (status) {
            debug("OpenPolicy Error: %ld\n", status);
        } else {

            /*
             * You have a handle to the policy object. Now, get the
             * domain information using LsaQueryInformationPolicy.
             */
            status = LsaQueryInformationPolicy(PolicyHandle,
                                               PolicyPrimaryDomainInformation,
                                               (PVOID *) & ppdiDomainInfo);
            if (status) {
                debug("LsaQueryInformationPolicy Error: %ld\n", status);
            } else {

                /* Get name in useable format */
                DomainName = AllocStrFromLSAStr(ppdiDomainInfo->Name);

                /*
                 * Check the Sid pointer, if it is null, the
                 * workstation is either a stand-alone computer
                 * or a member of a workgroup.
                 */
                if (ppdiDomainInfo->Sid) {

                    /*
                     * Member of a domain. Display it in debug mode.
                     */
                    debug("Member of Domain %s\n", DomainName);
                } else {
                    DomainName = NULL;
                }
            }
        }

        /*
         * Clean up all the memory buffers created by the LSA and
         * Net* APIs.
         */
        NetApiBufferFree(pwkiWorkstationInfo);
        LsaFreeMemory((LPVOID) ppdiDomainInfo);
    } else
        debug("NetWkstaGetInfo Error: %ld\n", netret);
    return DomainName;
}
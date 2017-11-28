int
Valid_Global_Groups(char *UserName, const char **Groups)
{
    int result = 0;
    WCHAR wszUserName[UNLEN + 1];	// Unicode user name

    WCHAR wszDomainControllerName[UNCLEN + 1];

    char NTDomain[DNLEN + UNLEN + 2];
    char *domain_qualify = NULL;
    char User[UNLEN + 1];
    size_t j;

    LPGROUP_USERS_INFO_0 pUsrBuf = NULL;
    LPGROUP_USERS_INFO_0 pTmpBuf;
    PDOMAIN_CONTROLLER_INFO pDCInfo = NULL;
    DWORD dwLevel = 0;
    DWORD dwPrefMaxLen = -1;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    NET_API_STATUS nStatus;
    DWORD i;
    DWORD dwTotalCount = 0;
    LPBYTE pBufTmp = NULL;

    strncpy(NTDomain, UserName, sizeof(NTDomain));

    for (j = 0; j < strlen(NTV_VALID_DOMAIN_SEPARATOR); j++) {
        if ((domain_qualify = strchr(NTDomain, NTV_VALID_DOMAIN_SEPARATOR[j])) != NULL)
            break;
    }
    if (domain_qualify == NULL) {
        strcpy(User, NTDomain);
        strcpy(NTDomain, DefaultDomain);
    } else {
        strcpy(User, domain_qualify + 1);
        domain_qualify[0] = '\0';
        strlwr(NTDomain);
    }

    debug("Valid_Global_Groups: checking group membership of '%s\\%s'.\n", NTDomain, User);

    /* Convert ANSI User Name to Unicode */

    MultiByteToWideChar(CP_ACP, 0, User,
                        strlen(User) + 1, wszUserName,
                        sizeof(wszUserName) / sizeof(wszUserName[0]));

    /* Query AD for a DC */

    if (DsGetDcName(NULL, NTDomain, NULL, NULL, DS_IS_FLAT_NAME | DS_RETURN_FLAT_NAME, &pDCInfo) != NO_ERROR) {
        fprintf(stderr, "%s DsGetDcName() failed.'\n", myname);
        if (pDCInfo != NULL)
            NetApiBufferFree(pDCInfo);
        return result;
    }
    /* Convert ANSI Domain Controller Name to Unicode */

    MultiByteToWideChar(CP_ACP, 0, pDCInfo->DomainControllerName,
                        strlen(pDCInfo->DomainControllerName) + 1, wszDomainControllerName,
                        sizeof(wszDomainControllerName) / sizeof(wszDomainControllerName[0]));

    debug("Using '%S' as DC for '%s' user's domain.\n", wszDomainControllerName, NTDomain);
    debug("DC Active Directory Site is %s\n", pDCInfo->DcSiteName);
    debug("Machine Active Directory Site is %s\n", pDCInfo->ClientSiteName);

    /*
     * Call the NetUserGetGroups function
     * specifying information level 0.
     */
    dwLevel = 0;
    pBufTmp = NULL;
    nStatus = NetUserGetGroups(wszDomainControllerName,
                               wszUserName,
                               dwLevel,
                               &pBufTmp,
                               dwPrefMaxLen,
                               &dwEntriesRead,
                               &dwTotalEntries);
    pUsrBuf = (LPGROUP_USERS_INFO_0) pBufTmp;
    /*
     * If the call succeeds,
     */
    if (nStatus == NERR_Success) {
        if ((pTmpBuf = pUsrBuf) != NULL) {
            for (i = 0; i < dwEntriesRead; i++) {
                assert(pTmpBuf != NULL);
                if (pTmpBuf == NULL) {
                    result = 0;
                    break;
                }
                if (wcstrcmparray(pTmpBuf->grui0_name, Groups) == 0) {
                    result = 1;
                    break;
                }
                pTmpBuf++;
                dwTotalCount++;
            }
        }
    } else {
        result = 0;
        fprintf(stderr, "%s NetUserGetGroups() failed.'\n", myname);
    }
    /*
     * Free the allocated memory.
     */
    if (pUsrBuf != NULL)
        NetApiBufferFree(pUsrBuf);
    if (pDCInfo != NULL)
        NetApiBufferFree((LPVOID) pDCInfo);
    return result;
}
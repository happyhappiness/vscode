int
Valid_Global_Groups(char *UserName, const char **Groups)
{
    int result = 0;
    WCHAR wszUser[DNLEN + UNLEN + 2];	/* Unicode user name */
    char NTDomain[DNLEN + UNLEN + 2];

    char *domain_qualify = NULL;
    char User[DNLEN + UNLEN + 2];
    size_t j;

    wchar_t *User_DN, *User_LDAP_path, *User_PrimaryGroup;
    wchar_t **wszGroups, **tmp;
    IADs *pUser;
    HRESULT hr;

    strncpy(NTDomain, UserName, sizeof(NTDomain));

    for (j = 0; j < strlen(NTV_VALID_DOMAIN_SEPARATOR); ++j) {
        if ((domain_qualify = strchr(NTDomain, NTV_VALID_DOMAIN_SEPARATOR[j])) != NULL)
            break;
    }
    if (domain_qualify == NULL) {
        strncpy(User, DefaultDomain, DNLEN);
        strcat(User, "\\");
        strncat(User, UserName, UNLEN);
        strncpy(NTDomain, DefaultDomain, DNLEN);
    } else {
        domain_qualify[0] = '\\';
        strncpy(User, NTDomain, DNLEN + UNLEN + 2);
        domain_qualify[0] = '\0';
    }

    debug("Valid_Global_Groups: checking group membership of '%s'.\n", User);

    /* Convert ANSI User Name to Unicode */

    MultiByteToWideChar(CP_ACP, 0, User,
                        strlen(User) + 1, wszUser,
                        sizeof(wszUser) / sizeof(wszUser[0]));

    /* Get CN of User */
    if ((User_DN = My_NameTranslate(wszUser, ADS_NAME_TYPE_NT4, ADS_NAME_TYPE_1779)) == NULL) {
        debug("Valid_Global_Groups: cannot get DN for '%s'.\n", User);
        return result;
    }
    wszGroups = build_groups_DN_array(Groups, NTDomain);

    User_LDAP_path = GetLDAPPath(User_DN, GC_MODE);

    hr = ADsGetObject(User_LDAP_path, &IID_IADs, (void **) &pUser);
    if (SUCCEEDED(hr)) {
        wchar_t *User_PrimaryGroup_Path;
        IADs *pGrp;

        User_PrimaryGroup = Get_primaryGroup(pUser);
        if (User_PrimaryGroup == NULL)
            debug("Valid_Global_Groups: cannot get Primary Group for '%s'.\n", User);
        else {
            add_User_Group(User_PrimaryGroup);
            User_PrimaryGroup_Path = GetLDAPPath(User_PrimaryGroup, GC_MODE);
            hr = ADsGetObject(User_PrimaryGroup_Path, &IID_IADs, (void **) &pGrp);
            if (SUCCEEDED(hr)) {
                hr = Recursive_Memberof(pGrp);
                pGrp->lpVtbl->Release(pGrp);
                safe_free(User_PrimaryGroup_Path);
                User_PrimaryGroup_Path = GetLDAPPath(User_PrimaryGroup, LDAP_MODE);
                hr = ADsGetObject(User_PrimaryGroup_Path, &IID_IADs, (void **) &pGrp);
                if (SUCCEEDED(hr)) {
                    hr = Recursive_Memberof(pGrp);
                    pGrp->lpVtbl->Release(pGrp);
                } else
                    debug("Valid_Global_Groups: ADsGetObject for %S failed, ERROR: %s\n", User_PrimaryGroup_Path, Get_WIN32_ErrorMessage(hr));
            } else
                debug("Valid_Global_Groups: ADsGetObject for %S failed, ERROR: %s\n", User_PrimaryGroup_Path, Get_WIN32_ErrorMessage(hr));
            safe_free(User_PrimaryGroup_Path);
        }
        hr = Recursive_Memberof(pUser);
        pUser->lpVtbl->Release(pUser);
        safe_free(User_LDAP_path);
        User_LDAP_path = GetLDAPPath(User_DN, LDAP_MODE);
        hr = ADsGetObject(User_LDAP_path, &IID_IADs, (void **) &pUser);
        if (SUCCEEDED(hr)) {
            hr = Recursive_Memberof(pUser);
            pUser->lpVtbl->Release(pUser);
        } else
            debug("Valid_Global_Groups: ADsGetObject for %S failed, ERROR: %s\n", User_LDAP_path, Get_WIN32_ErrorMessage(hr));

        tmp = User_Groups;
        while (*tmp) {
            if (wccmparray(*tmp, wszGroups) == 0) {
                result = 1;
                break;
            }
            ++tmp;
        }
    } else
        debug("Valid_Global_Groups: ADsGetObject for %S failed, ERROR: %s\n", User_LDAP_path, Get_WIN32_ErrorMessage(hr));

    safe_free(User_DN);
    safe_free(User_LDAP_path);
    safe_free(User_PrimaryGroup);
    tmp = wszGroups;
    while (*tmp) {
        safe_free(*tmp);
        ++tmp;
    }
    safe_free(wszGroups);

    tmp = User_Groups;
    while (*tmp) {
        safe_free(*tmp);
        ++tmp;
    }
    safe_free(User_Groups);
    User_Groups_Count = 0;

    return result;
}
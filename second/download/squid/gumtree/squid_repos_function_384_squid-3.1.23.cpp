int
Valid_User(char *UserName, char *Password, char *Group)
{
    int result = NTV_SERVER_ERROR;
    size_t i;
    char NTDomain[256];
    char *domain_qualify = NULL;
    char DomainUser[256];
    char User[256];

    errormsg = NTV_SERVER_ERROR_MSG;
    strncpy(NTDomain, UserName, sizeof(NTDomain));

    for (i=0; i < strlen(NTV_VALID_DOMAIN_SEPARATOR); i++) {
        if ((domain_qualify = strchr(NTDomain, NTV_VALID_DOMAIN_SEPARATOR[i])) != NULL)
            break;
    }
    if (domain_qualify == NULL) {
        strcpy(User, NTDomain);
        strcpy(NTDomain, Default_NTDomain);
    } else {
        strcpy(User, domain_qualify + 1);
        domain_qualify[0] = '\0';
    }
    /* Log the client on to the local computer. */
    if (!SSP_LogonUser(User, Password, NTDomain)) {
        result = NTV_LOGON_ERROR;
        errormsg = NTV_LOGON_ERROR_MSG;
        debug("%s\n", errormsg);
    } else {
        result = NTV_NO_ERROR;
        if (strcmp(NTDomain, NTV_DEFAULT_DOMAIN) == 0)
            strcpy(DomainUser, User);
        else {
            strcpy(DomainUser, NTDomain);
            strcat(DomainUser, "\\");
            strcat(DomainUser, User);
        }
        if (UseAllowedGroup) {
            if (!Valid_Group(DomainUser, NTAllowedGroup)) {
                result = NTV_GROUP_ERROR;
                errormsg = NTV_GROUP_ERROR_MSG;
                debug("%s\n", errormsg);
            }
        }
        if (UseDisallowedGroup) {
            if (Valid_Group(DomainUser, NTDisAllowedGroup)) {
                result = NTV_GROUP_ERROR;
                errormsg = NTV_GROUP_ERROR_MSG;
                debug("%s\n", errormsg);
            }
        }
    }
    return result;
}
int
ntlm_check_auth(ntlm_authenticate * auth, char *user, char *domain, int auth_length)
{
    int x;
    int rv;
    char credentials[DNLEN+UNLEN+2];    /* we can afford to waste */

    if (!NTLM_LocalCall) {

        user[0] = '\0';
        domain[0] = '\0';
        x = ntlm_unpack_auth(auth, user, domain, auth_length);

        if (x != NTLM_ERR_NONE)
            return x;

        if (domain[0] == '\0') {
            debug("No domain supplied. Returning no-auth\n");
            return NTLM_BAD_REQUEST;
        }
        if (user[0] == '\0') {
            debug("No username supplied. Returning no-auth\n");
            return NTLM_BAD_REQUEST;
        }
        debug("checking domain: '%s', user: '%s'\n", domain, user);

    } else
        debug("checking local user\n");

    snprintf(credentials, DNLEN+UNLEN+2, "%s\\%s", domain, user);

    rv = SSP_ValidateNTLMCredentials(auth, auth_length, credentials);

    debug("Login attempt had result %d\n", rv);

    if (!rv) {          /* failed */
        return NTLM_SSPI_ERROR;
    }

    if (UseAllowedGroup) {
        if (!Valid_Group(credentials, NTAllowedGroup)) {
            debug("User %s not in allowed Group %s\n", credentials, NTAllowedGroup);
            return NTLM_BAD_NTGROUP;
        }
    }
    if (UseDisallowedGroup) {
        if (Valid_Group(credentials, NTDisAllowedGroup)) {
            debug("User %s is in denied Group %s\n", credentials, NTDisAllowedGroup);
            return NTLM_BAD_NTGROUP;
        }
    }

    debug("credentials: %s\n", credentials);
    return NTLM_ERR_NONE;
}
char *
ntlm_check_auth(ntlm_authenticate * auth, int auth_length)
{
    int rv;
    char domain[DNLEN+1];
    char user[UNLEN+1];
    static char credentials[DNLEN+UNLEN+2];	/* we can afford to waste */

    lstring tmp;

    if (!NTLM_LocalCall) {

        tmp = ntlm_fetch_string((char *) auth, auth_length, &auth->domain);

        if (tmp.str == NULL || tmp.l == 0) {
            debug("No domain supplied. Returning no-auth\n");
            ntlm_errno = NTLM_BAD_REQUEST;
            return NULL;
        }
        if (Use_Unicode) {
            /* copy unicode buffer */
            WideCharToMultiByte(CP_ACP, 0, (LPCWSTR) tmp.str, tmp.l, domain, DNLEN, NULL, NULL );
            /* add null termination */
            domain[tmp.l / sizeof(WCHAR)] = '\0';
        } else {
            if (tmp.l > DNLEN) {
                debug("Domain string exceeds %d bytes, rejecting\n", DNLEN);
                ntlm_errno = NTLM_BAD_REQUEST;
                return NULL;
            }
            memcpy(domain, tmp.str, tmp.l);
            domain[tmp.l] = '\0';
        }
        tmp = ntlm_fetch_string((char *) auth, auth_length, &auth->user);
        if (tmp.str == NULL || tmp.l == 0) {
            debug("No username supplied. Returning no-auth\n");
            ntlm_errno = NTLM_BAD_REQUEST;
            return NULL;
        }
        if (Use_Unicode) {
            /* copy unicode buffer */
            WideCharToMultiByte(CP_ACP, 0, (LPCWSTR) tmp.str, tmp.l, user, UNLEN, NULL, NULL );
            /* add null termination */
            user[tmp.l / sizeof(WCHAR)] = '\0';
        } else {
            if (tmp.l > UNLEN) {
                debug("Username string exceeds %d bytes, rejecting\n", UNLEN);
                ntlm_errno = NTLM_BAD_REQUEST;
                return NULL;
            }
            memcpy(user, tmp.str, tmp.l);
            user[tmp.l] = '\0';
        }
        debug("checking domain: '%s', user: '%s'\n", domain, user);

    } else
        debug("checking local user\n");

    rv = SSP_ValidateNTLMCredentials(auth, auth_length, credentials);

    debug("Login attempt had result %d\n", rv);

    if (!rv) {			/* failed */
        ntlm_errno = NTLM_SSPI_ERROR;
        return NULL;
    }

    if (UseAllowedGroup) {
        if (!Valid_Group(credentials, NTAllowedGroup)) {
            ntlm_errno = NTLM_BAD_NTGROUP;
            debug("User %s not in allowed Group %s\n", credentials, NTAllowedGroup);
            return NULL;
        }
    }
    if (UseDisallowedGroup) {
        if (Valid_Group(credentials, NTDisAllowedGroup)) {
            ntlm_errno = NTLM_BAD_NTGROUP;
            debug("User %s is in denied Group %s\n", credentials, NTDisAllowedGroup);
            return NULL;
        }
    }

    debug("credentials: %s\n", credentials);
    return credentials;
}
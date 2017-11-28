        ntlm_errno = NTLM_ERR_LOGON;
        return NULL;
    }
    memcpy(user, tmp.str, tmp.l);
    *(user + tmp.l) = '\0';

    /* Authenticating against the NT response doesn't seem to work... */
    tmp = ntlm_fetch_string(&(auth->hdr), auth_length, &auth->lmresponse, auth->flags);
    if (tmp.str == NULL || tmp.l == 0) {
        fprintf(stderr, "No auth at all. Returning no-auth\n");
        ntlm_errno = NTLM_ERR_LOGON;
        return NULL;
    }
    if (tmp.l > MAX_PASSWD_LEN) {
        debug("Password string exceeds %d bytes, rejecting\n", MAX_PASSWD_LEN);
        ntlm_errno = NTLM_ERR_LOGON;
        return NULL;
    }

    memcpy(pass, tmp.str, tmp.l);
    pass[min(MAX_PASSWD_LEN,tmp.l)] = '\0';

#if 1
    debug("Empty LM pass detection: user: '%s', ours:'%s', his: '%s' (length: %d)\n",
          user,lmencoded_empty_pass,tmp.str,tmp.l);
    if (memcmp(tmp.str,lmencoded_empty_pass,ENCODED_PASS_LEN)==0) {
        fprintf(stderr,"Empty LM password supplied for user %s\\%s. "
                "No-auth\n",domain,user);
        ntlm_errno=NTLM_ERR_LOGON;
        return NULL;
    }

    tmp = ntlm_fetch_string(&(auth->hdr), auth_length, &auth->ntresponse, auth->flags);
    if (tmp.str != NULL && tmp.l != 0) {
        debug("Empty NT pass detection: user: '%s', ours:'%s', his: '%s' (length: %d)\n",
              user,ntencoded_empty_pass,tmp.str,tmp.l);
        if (memcmp(tmp.str,lmencoded_empty_pass,ENCODED_PASS_LEN)==0) {
            fprintf(stderr,"ERROR: Empty NT password supplied for user %s\\%s. No-auth\n", domain, user);
            ntlm_errno = NTLM_ERR_LOGON;
            return NULL;
        }
    }
#endif

    /* TODO: check against empty password!!!!! */

    debug("checking domain: '%s', user: '%s', pass='%s'\n", domain, user, pass);

    rv = SMB_Logon_Server(handle, user, pass, domain, 1);
    debug("Login attempt had result %d\n", rv);

    if (rv != NTLM_ERR_NONE) {	/* failed */
        ntlm_errno = rv;
        return NULL;
    }
    *(user - 1) = '\\';		/* hack. Performing, but ugly. */

    debug("credentials: %s\n", credentials);
    return credentials;
}

extern "C" void timeout_during_auth(int signum);

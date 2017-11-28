BOOL GenServerContext(PAUTH_SEQ pAS, PVOID pIn, DWORD cbIn, PVOID pOut,
                      PDWORD pcbOut, PBOOL pfDone, char * credentials)
{
    /*
     *   Routine Description:
     *
     *   Takes an input buffer coming from the client and returns a buffer
     *   to be sent to the client.  Also returns an indication of whether or
     *   not the context is complete.
     *
     *   Return Value:
     *
     *   Returns TRUE if successful; otherwise FALSE.
     */

    SecBufferDesc   sbdOut;
    SecBuffer       sbOut;
    SecBufferDesc   sbdIn;
    SecBuffer       sbIn;
    ULONG           fContextAttr;
    SecPkgContext_Names namebuffer;

    if (!pAS->fInitialized)  {
        SecurityStatus = _AcquireCredentialsHandle(NULL, (SEC_CHAR*) _T(SSP_Package_InUse),
                         SECPKG_CRED_INBOUND, NULL, NULL, NULL, NULL, &pAS->hcred,
                         &pAS->hcredLifeTime);
#if SSP_DEBUG
        fprintf(stderr, "AcquireCredentialsHandle returned: %x\n", SecurityStatus);
#endif
        if (SecurityStatus < 0) {
#if SSP_DEBUG
            fprintf(stderr, "AcquireCredentialsHandle failed: %x\n", SecurityStatus);
#endif
            return FALSE;
        }
        pAS->fHaveCredHandle = TRUE;
    }

    /* Prepare output buffer */
    sbdOut.ulVersion = 0;
    sbdOut.cBuffers = 1;
    sbdOut.pBuffers = &sbOut;
    sbOut.cbBuffer = *pcbOut;
    sbOut.BufferType = SECBUFFER_TOKEN;
    sbOut.pvBuffer = pOut;

    /* Prepare input buffer */
    sbdIn.ulVersion = 0;
    sbdIn.cBuffers = 1;
    sbdIn.pBuffers = &sbIn;
    sbIn.cbBuffer = cbIn;
    sbIn.BufferType = SECBUFFER_TOKEN;
    sbIn.pvBuffer = pIn;
    SecurityStatus = _AcceptSecurityContext(&pAS->hcred,
                                            pAS->fInitialized ? &pAS->hctxt : NULL, &sbdIn, (NTLM_mode == SSP_NTLM) ? ASC_REQ_DELEGATE : 0,
                                            SECURITY_NATIVE_DREP, &pAS->hctxt, &sbdOut, &fContextAttr,
                                            &pAS->hctxtLifeTime);
#if SSP_DEBUG
    fprintf(stderr, "AcceptSecurityContext returned: %x\n", SecurityStatus);
#endif
    if (SecurityStatus < 0) {
#if SSP_DEBUG
        fprintf(stderr, "AcceptSecurityContext failed: %x\n", SecurityStatus);
#endif
        return FALSE;
    }
    pAS->fHaveCtxtHandle = TRUE;

    /* If necessary, complete token */
    if (SecurityStatus == SEC_I_COMPLETE_NEEDED || SecurityStatus == SEC_I_COMPLETE_AND_CONTINUE) {
        SecurityStatus = _CompleteAuthToken(&pAS->hctxt, &sbdOut);
#if SSP_DEBUG
        fprintf(stderr, "CompleteAuthToken returned: %x\n", SecurityStatus);
#endif
        if (SecurityStatus < 0) {
#if SSP_DEBUG
            fprintf(stderr, "CompleteAuthToken failed: %x\n", SecurityStatus);
#endif
            return FALSE;
        }
    }

    if ((credentials != NULL) &&
            !(SecurityStatus == SEC_I_CONTINUE_NEEDED || SecurityStatus == SEC_I_COMPLETE_AND_CONTINUE)) {
        SecurityStatus = _QueryContextAttributes(&pAS->hctxt, SECPKG_ATTR_NAMES, &namebuffer);
#if SSP_DEBUG
        fprintf(stderr, "QueryContextAttributes returned: %x\n", SecurityStatus);
#endif
        if (SecurityStatus < 0) {
#if SSP_DEBUG
            fprintf(stderr, "QueryContextAttributes failed: %x\n", SecurityStatus);
#endif
            return FALSE;
        }
        strncpy(credentials, namebuffer.sUserName, SSP_MAX_CRED_LEN);
    }

    *pcbOut = sbOut.cbBuffer;
    if (!pAS->fInitialized)
        pAS->fInitialized = TRUE;
    *pfDone = !(SecurityStatus == SEC_I_CONTINUE_NEEDED
                || SecurityStatus == SEC_I_COMPLETE_AND_CONTINUE);
    return TRUE;
}
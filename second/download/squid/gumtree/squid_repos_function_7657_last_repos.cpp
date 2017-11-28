BOOL GenClientContext(PAUTH_SEQ pAS, PSEC_WINNT_AUTH_IDENTITY pAuthIdentity,
                      PVOID pIn, DWORD cbIn, PVOID pOut, PDWORD pcbOut, PBOOL pfDone)
{
    /*
     *  Routine Description:
     *
     *  Optionally takes an input buffer coming from the server and returns
     *  a buffer of information to send back to the server. Also returns
     *  an indication of whether or not the context is complete.
     *
     *  Return Value:
     *  Returns TRUE if successful; otherwise FALSE.
     */
    TimeStamp       tsExpiry;
    SecBufferDesc   sbdOut;
    SecBuffer       sbOut;
    SecBufferDesc   sbdIn;
    SecBuffer       sbIn;
    ULONG           fContextAttr;

    if (!pAS->fInitialized) {
        SecurityStatus = _AcquireCredentialsHandle(NULL, (SEC_CHAR*) _T(SSP_Package_InUse),
                         SECPKG_CRED_OUTBOUND, NULL, (NTLM_mode == SSP_NTLM) ? NULL : pAuthIdentity, NULL, NULL,
                         &pAS->hcred, &tsExpiry);
        if (SecurityStatus < 0)
            return FALSE;
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
    if (pAS->fInitialized)  {
        sbdIn.ulVersion = 0;
        sbdIn.cBuffers = 1;
        sbdIn.pBuffers = &sbIn;
        sbIn.cbBuffer = cbIn;
        sbIn.BufferType = SECBUFFER_TOKEN;
        sbIn.pvBuffer = pIn;
    }
    SecurityStatus = _InitializeSecurityContext(&pAS->hcred,
                     pAS->fInitialized ? &pAS->hctxt : NULL, NULL, 0, 0,
                     SECURITY_NATIVE_DREP, pAS->fInitialized ? &sbdIn : NULL,
                     0, &pAS->hctxt, &sbdOut, &fContextAttr, &tsExpiry);
    if (SecurityStatus < 0)
        return FALSE;
    pAS->fHaveCtxtHandle = TRUE;

    /* If necessary, complete token */
    if (SecurityStatus == SEC_I_COMPLETE_NEEDED || SecurityStatus == SEC_I_COMPLETE_AND_CONTINUE) {
        SecurityStatus = _CompleteAuthToken(&pAS->hctxt, &sbdOut);
        if (SecurityStatus < 0)
            return FALSE;
    }
    *pcbOut = sbOut.cbBuffer;
    if (!pAS->fInitialized)
        pAS->fInitialized = TRUE;
    *pfDone = !(SecurityStatus == SEC_I_CONTINUE_NEEDED
                || SecurityStatus == SEC_I_COMPLETE_AND_CONTINUE );
    return TRUE;
}
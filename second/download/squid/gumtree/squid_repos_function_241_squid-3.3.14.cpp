wchar_t *
Get_primaryGroup(IADs * pUser)
{
    HRESULT hr;
    VARIANT var;
    unsigned User_primaryGroupID;
    char tmpSID[SECURITY_MAX_SID_SIZE * 2];
    wchar_t *wc = NULL, *result = NULL;
    int wcsize;

    VariantInit(&var);

    /* Get the primaryGroupID property */
    hr = pUser->lpVtbl->Get(pUser, L"primaryGroupID", &var);
    if (SUCCEEDED(hr)) {
        User_primaryGroupID = var.n1.n2.n3.uintVal;
    } else {
        debug("Get_primaryGroup: cannot get primaryGroupID, ERROR: %s\n", Get_WIN32_ErrorMessage(hr));
        VariantClear(&var);
        return result;
    }
    VariantClear(&var);

    /*Get the objectSid property */
    hr = pUser->lpVtbl->Get(pUser, L"objectSid", &var);
    if (SUCCEEDED(hr)) {
        PSID pObjectSID;
        LPBYTE pByte = NULL;
        char *szSID = NULL;
        hr = GetLPBYTEtoOctetString(&var, &pByte);

        pObjectSID = (PSID) pByte;

        /* Convert SID to string. */
        ConvertSidToStringSid(pObjectSID, &szSID);
        CoTaskMemFree(pByte);

        *(strrchr(szSID, '-') + 1) = '\0';
        sprintf(tmpSID, "%s%u", szSID, User_primaryGroupID);

        wcsize = MultiByteToWideChar(CP_ACP, 0, tmpSID, -1, wc, 0);
        wc = (wchar_t *) xmalloc(wcsize * sizeof(wchar_t));
        MultiByteToWideChar(CP_ACP, 0, tmpSID, -1, wc, wcsize);
        LocalFree(szSID);

        result = My_NameTranslate(wc, ADS_NAME_TYPE_SID_OR_SID_HISTORY_NAME, ADS_NAME_TYPE_1779);
        safe_free(wc);

        if (result == NULL)
            debug("Get_primaryGroup: cannot get DN for %s.\n", tmpSID);
        else
            debug("Get_primaryGroup: Primary group DN: %S.\n", result);
    } else
        debug("Get_primaryGroup: cannot get objectSid, ERROR: %s\n", Get_WIN32_ErrorMessage(hr));
    VariantClear(&var);
    return result;
}
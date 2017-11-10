void ErrorMessage(LPCSTR szError, BOOL bFatal)
{
    LPVOID lpMsgBuf = NULL;
    if (szError) {
        MessageBox(NULL, szError, g_lpMsg[IDS_MSG_ERROR - IDS_MSG_FIRST],
                   MB_OK | (bFatal ? MB_ICONERROR : MB_ICONEXCLAMATION));
    }
    else {
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                      FORMAT_MESSAGE_FROM_SYSTEM |
                      FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, GetLastError(), g_LangID,
                      (LPSTR) &lpMsgBuf, 0, NULL);
        MessageBox(NULL, (LPCSTR)lpMsgBuf, 
                   g_lpMsg[IDS_MSG_ERROR - IDS_MSG_FIRST],
                   MB_OK | (bFatal ? MB_ICONERROR : MB_ICONEXCLAMATION));
        LocalFree(lpMsgBuf);
    }
    if (bFatal) {
        PostQuitMessage(0);
    }
}
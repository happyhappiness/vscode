static DWORD WINAPI ConsoleOutputThread(LPVOID lpThreadParameter)
{
    static BYTE lpBuffer[MAX_PATH+1];
    int nPtr = 0;
    BYTE ch;
    DWORD dwReaded;

    while (ReadFile(g_hpipeOutRead, &ch, 1, &dwReaded, NULL) == TRUE)
    {
        if (dwReaded > 0)
        {
            if (ch == '\n' || nPtr >= MAX_PATH)
            {
                lpBuffer[nPtr] = '\0';
                addListBoxStringA(g_hwndStdoutList, lpBuffer);
                nPtr = 0;
            }
            else if (ch == '\t' && nPtr < (MAX_PATH - 4))
            {
                int i;
                for (i = 0; i < 4; ++i) {
                    lpBuffer[nPtr++] = ' ';
                }
            }
            else if (ch != '\r') {
                lpBuffer[nPtr++] = ch;
            }
        }
    }
    CloseHandle(g_hpipeInWrite);
    CloseHandle(g_hpipeOutRead);
    CloseHandle(g_hpipeStdError);
    return 0;
}
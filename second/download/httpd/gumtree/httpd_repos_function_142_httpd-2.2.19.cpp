static void addListBoxStringA(HWND hListBox, LPSTR lpStr)
{
    static int nItems = 0;
    TCHAR WStr[16384];

    if (!g_bDlgServiceOn) {
        return;
    }
    if (!MultiByteToWideChar(CP_ACP, 0, lpStr, (int)strlen(lpStr) + 1,
                             WStr, (int) (sizeof(WStr) / sizeof(TCHAR))))
        return;
    ++nItems;
    if (nItems > MAX_LOADSTRING)
    {
        SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
        nItems = 1;
    }
    ListBox_SetCurSel(hListBox,
                      ListBox_AddString(hListBox, WStr));
}
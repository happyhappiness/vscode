static void addListBoxString(HWND hListBox, LPTSTR lpStr)
{
    static int nItems = 0;
    if (!g_bDlgServiceOn) {
        return;
    }
    ++nItems;
    if (nItems > MAX_LOADSTRING)
    {
        SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
        nItems = 1;
    }
    ListBox_SetCurSel(hListBox,
                      ListBox_AddString(hListBox, lpStr));

}
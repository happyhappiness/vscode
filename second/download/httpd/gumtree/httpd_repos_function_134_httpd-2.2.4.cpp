static void addListBoxItem(HWND hDlg, LPSTR lpStr, HBITMAP hBmp)
{
    LRESULT nItem;

    nItem = SendMessage(hDlg, LB_ADDSTRING, 0, (LPARAM)lpStr);
    SendMessage(hDlg, LB_SETITEMDATA, nItem, (LPARAM)hBmp);
}
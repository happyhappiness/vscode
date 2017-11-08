LPTSTR GetStringRes(int id)
{
    static TCHAR buffer[MAX_PATH];

    buffer[0] = 0;
    LoadString(GetModuleHandle(NULL), id, buffer, MAX_PATH);
    return buffer;
}
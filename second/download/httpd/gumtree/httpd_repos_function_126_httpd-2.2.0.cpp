LPSTR GetStringRes(int id)
{
    static CHAR buffer[MAX_PATH];

    buffer[0] = 0;
    LoadString(GetModuleHandle(NULL), id, buffer, MAX_PATH);
    return buffer;
}
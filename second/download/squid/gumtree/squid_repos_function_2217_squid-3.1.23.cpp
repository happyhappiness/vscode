static void
idnsParseWIN32SearchList(const char * Separator)
{
    char *t;
    char *token;
    HKEY hndKey;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_TCPIP_PARA, 0, KEY_QUERY_VALUE, &hndKey) == ERROR_SUCCESS) {
        DWORD Type = 0;
        DWORD Size = 0;
        LONG Result;
        Result = RegQueryValueEx(hndKey, "Domain", NULL, &Type, NULL, &Size);

        if (Result == ERROR_SUCCESS && Size) {
            t = (char *) xmalloc(Size);
            RegQueryValueEx(hndKey, "Domain", NULL, &Type, (LPBYTE) t, &Size);
            debugs(78, 1, "Adding domain " << t << " from Registry");
            idnsAddPathComponent(t);
            xfree(t);
        }
        Result = RegQueryValueEx(hndKey, "SearchList", NULL, &Type, NULL, &Size);

        if (Result == ERROR_SUCCESS && Size) {
            t = (char *) xmalloc(Size);
            RegQueryValueEx(hndKey, "SearchList", NULL, &Type, (LPBYTE) t, &Size);
            token = strtok(t, Separator);

            while (token) {
                idnsAddPathComponent(token);
                debugs(78, 1, "Adding domain " << token << " from Registry");
                token = strtok(NULL, Separator);
            }
            xfree(t);
        }

        RegCloseKey(hndKey);
    }
    if (npc == 0 && (t = (char *) getMyHostname())) {
        t = strchr(t, '.');
        if (t)
            idnsAddPathComponent(t + 1);
    }
}
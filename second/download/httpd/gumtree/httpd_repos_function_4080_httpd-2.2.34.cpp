static int can_create_global_maps(void)
{
    BOOL ok, has_priv;
    LUID priv_id;
    PRIVILEGE_SET privs;
    HANDLE hToken;

    ok = OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, TRUE, &hToken);
    if (!ok && GetLastError() == ERROR_NO_TOKEN) {
        /* no thread-specific access token, so try to get process access token
         */
        ok = OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);
    }

    if (ok) {
        ok = LookupPrivilegeValue(NULL, SE_CREATE_GLOBAL_NAME, &priv_id);
    }

    if (ok) {
        privs.PrivilegeCount = 1;
        privs.Control = PRIVILEGE_SET_ALL_NECESSARY;
        privs.Privilege[0].Luid = priv_id;
        privs.Privilege[0].Attributes = SE_PRIVILEGE_ENABLED;
        ok = PrivilegeCheck(hToken, &privs, &has_priv);
    }

    if (ok && !has_priv) {
        return 0;
    }
    else {
        return 1;
    }
}
wchar_t *
GetLDAPPath(wchar_t * Base_DN, int query_mode)
{
    wchar_t *wc;

    wc = (wchar_t *) xmalloc((wcslen(Base_DN) + 8) * sizeof(wchar_t));

    if (query_mode == LDAP_MODE)
        wcscpy(wc, L"LDAP://");
    else
        wcscpy(wc, L"GC://");
    wcscat(wc, Base_DN);

    return wc;
}
static void
idnsParseWIN32Registry(void)
{
    char *t;
    char *token;
    HKEY hndKey, hndKey2;

    switch (WIN32_OS_version) {

    case _WIN_OS_WINNT:
        /* get nameservers from the Windows NT registry */

        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_TCPIP_PARA, 0, KEY_QUERY_VALUE, &hndKey) == ERROR_SUCCESS) {
            DWORD Type = 0;
            DWORD Size = 0;
            LONG Result;
            Result = RegQueryValueEx(hndKey, "DhcpNameServer", NULL, &Type, NULL, &Size);

            if (Result == ERROR_SUCCESS && Size) {
                t = (char *) xmalloc(Size);
                RegQueryValueEx(hndKey, "DhcpNameServer", NULL, &Type, (LPBYTE) t, &Size);
                token = strtok(t, ", ");

                while (token) {
                    idnsAddNameserver(token);
                    debugs(78, 1, "Adding DHCP nameserver " << token << " from Registry");
                    token = strtok(NULL, ",");
                }
                xfree(t);
            }

            Result = RegQueryValueEx(hndKey, "NameServer", NULL, &Type, NULL, &Size);

            if (Result == ERROR_SUCCESS && Size) {
                t = (char *) xmalloc(Size);
                RegQueryValueEx(hndKey, "NameServer", NULL, &Type, (LPBYTE) t, &Size);
                token = strtok(t, ", ");

                while (token) {
                    debugs(78, 1, "Adding nameserver " << token << " from Registry");
                    idnsAddNameserver(token);
                    token = strtok(NULL, ", ");
                }
                xfree(t);
            }

            RegCloseKey(hndKey);
        }

        idnsParseWIN32SearchList(" ");

        break;

    case _WIN_OS_WIN2K:

    case _WIN_OS_WINXP:

    case _WIN_OS_WINNET:

    case _WIN_OS_WINLON:

    case _WIN_OS_WIN7:
        /* get nameservers from the Windows 2000 registry */
        /* search all interfaces for DNS server addresses */

        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_TCPIP_PARA_INTERFACES, 0, KEY_READ, &hndKey) == ERROR_SUCCESS) {
            int i;
            DWORD MaxSubkeyLen, InterfacesCount;
            char *keyname;
            FILETIME ftLastWriteTime;

            if (RegQueryInfoKey(hndKey, NULL, NULL, NULL, &InterfacesCount, &MaxSubkeyLen, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
                keyname = (char *) xmalloc(++MaxSubkeyLen);
                for (i = 0; i < (int) InterfacesCount; i++) {
                    DWORD j;
                    j = MaxSubkeyLen;
                    if (RegEnumKeyEx(hndKey, i, keyname, &j, NULL, NULL, NULL, &ftLastWriteTime) == ERROR_SUCCESS) {
                        char *newkeyname;
                        newkeyname = (char *) xmalloc(sizeof(REG_TCPIP_PARA_INTERFACES) + j + 2);
                        strcpy(newkeyname, REG_TCPIP_PARA_INTERFACES);
                        strcat(newkeyname, "\\");
                        strcat(newkeyname, keyname);
                        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, newkeyname, 0, KEY_QUERY_VALUE, &hndKey2) == ERROR_SUCCESS) {
                            DWORD Type = 0;
                            DWORD Size = 0;
                            LONG Result;
                            Result = RegQueryValueEx(hndKey2, "DhcpNameServer", NULL, &Type, NULL, &Size);
                            if (Result == ERROR_SUCCESS && Size) {
                                t = (char *) xmalloc(Size);
                                RegQueryValueEx(hndKey2, "DhcpNameServer", NULL, &Type, (LPBYTE)t, &Size);
                                token = strtok(t, ", ");
                                while (token) {
                                    debugs(78, 1, "Adding DHCP nameserver " << token << " from Registry");
                                    idnsAddNameserver(token);
                                    token = strtok(NULL, ", ");
                                }
                                xfree(t);
                            }

                            Result = RegQueryValueEx(hndKey2, "NameServer", NULL, &Type, NULL, &Size);
                            if (Result == ERROR_SUCCESS && Size) {
                                t = (char *) xmalloc(Size);
                                RegQueryValueEx(hndKey2, "NameServer", NULL, &Type, (LPBYTE)t, &Size);
                                token = strtok(t, ", ");
                                while (token) {
                                    debugs(78, 1, "Adding nameserver " << token << " from Registry");
                                    idnsAddNameserver(token);
                                    token = strtok(NULL, ", ");
                                }

                                xfree(t);
                            }

                            RegCloseKey(hndKey2);
                        }

                        xfree(newkeyname);
                    }
                }

                xfree(keyname);
            }

            RegCloseKey(hndKey);
        }

        idnsParseWIN32SearchList(", ");

        break;

    case _WIN_OS_WIN95:

    case _WIN_OS_WIN98:

    case _WIN_OS_WINME:
        /* get nameservers from the Windows 9X registry */

        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_VXD_MSTCP, 0, KEY_QUERY_VALUE, &hndKey) == ERROR_SUCCESS) {
            DWORD Type = 0;
            DWORD Size = 0;
            LONG Result;
            Result = RegQueryValueEx(hndKey, "NameServer", NULL, &Type, NULL, &Size);

            if (Result == ERROR_SUCCESS && Size) {
                t = (char *) xmalloc(Size);
                RegQueryValueEx(hndKey, "NameServer", NULL, &Type, (LPBYTE) t, &Size);
                token = strtok(t, ", ");

                while (token) {
                    debugs(78, 1, "Adding nameserver " << token << " from Registry");
                    idnsAddNameserver(token);
                    token = strtok(NULL, ", ");
                }
                xfree(t);
            }

            RegCloseKey(hndKey);
        }

        break;

    default:
        debugs(78, 1, "Failed to read nameserver from Registry: Unknown System Type.");
        return;
    }
}
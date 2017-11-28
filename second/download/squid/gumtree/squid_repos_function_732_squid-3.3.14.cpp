void
WIN32_SetServiceCommandLine()
{
    if (!WIN32_Service_name)
        WIN32_Service_name = xstrdup(_WIN_SQUID_DEFAULT_SERVICE_NAME);

    strcat(REGKEY, WIN32_Service_name);

    keys[4] = WIN32_Service_name;

    /* Now store the Service Command Line in the registry */
    WIN32_StoreKey(COMMANDLINE, REG_SZ, (unsigned char *) WIN32_Command_Line, strlen(WIN32_Command_Line) + 1);
}
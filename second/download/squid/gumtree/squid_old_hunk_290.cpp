    fclose (fp);
}

int
getMyPort(void)
{
    if (Config.Sockaddr.http)
        return Config.Sockaddr.http->s.GetPort();

#if USE_SSL

    if (Config.Sockaddr.https)
        return Config.Sockaddr.https->http.s.GetPort();

#endif

    fatal("No port defined");

    return 0;			/* NOT REACHED */
}

/*
 * Set the umask to at least the given mask. This is in addition
 * to the umask set at startup
 */

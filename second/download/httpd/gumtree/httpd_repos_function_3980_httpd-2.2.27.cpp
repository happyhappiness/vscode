static int os2_fn_link()
{
    DosEnterCritSec(); /* Stop two threads doing this at the same time */

    if (apr_os2_socket == os2_socket_init) {
        ULONG rc;
        char errorstr[200];

        rc = DosLoadModule(errorstr, sizeof(errorstr), "SO32DLL", &hSO32DLL);

        if (rc)
            return APR_OS2_STATUS(rc);

        rc = DosQueryProcAddr(hSO32DLL, 0, "SOCKET", &apr_os2_socket);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "SELECT", &apr_os2_select);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "SOCK_ERRNO", &apr_os2_sock_errno);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "ACCEPT", &apr_os2_accept);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "BIND", &apr_os2_bind);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "CONNECT", &apr_os2_connect);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "GETPEERNAME", &apr_os2_getpeername);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "GETSOCKNAME", &apr_os2_getsockname);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "GETSOCKOPT", &apr_os2_getsockopt);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "IOCTL", &apr_os2_ioctl);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "LISTEN", &apr_os2_listen);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "RECV", &apr_os2_recv);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "SEND", &apr_os2_send);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "SETSOCKOPT", &apr_os2_setsockopt);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "SHUTDOWN", &apr_os2_shutdown);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "SOCLOSE", &apr_os2_soclose);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "WRITEV", &apr_os2_writev);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "SENDTO", &apr_os2_sendto);

        if (!rc)
            rc = DosQueryProcAddr(hSO32DLL, 0, "RECVFROM", &apr_os2_recvfrom);

        if (rc)
            return APR_OS2_STATUS(rc);
    }

    DosExitCritSec();
    return APR_SUCCESS;
}
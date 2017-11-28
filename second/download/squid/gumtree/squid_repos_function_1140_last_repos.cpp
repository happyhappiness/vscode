static int
ipcSend(int cwfd, const char *buf, int len)
{
    int x = send(cwfd, (const void *)buf, len, 0);

    if (x < 0) {
        int xerrno = errno;
        debugs(54, DBG_CRITICAL, "sendto FD " << cwfd << ": " << xstrerr(xerrno));
        debugs(54, DBG_CRITICAL, "ipcCreate: CHILD: hello write test failed");
    }

    return x;
}
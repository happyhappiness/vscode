static int
ipcSend(int cwfd, const char *buf, int len)
{
    int x;

    x = send(cwfd, (const void *)buf, len, 0);

    if (x < 0) {
        debugs(54, DBG_CRITICAL, "sendto FD " << cwfd << ": " << xstrerror());
        debugs(54, DBG_CRITICAL, "ipcCreate: CHILD: hello write test failed");
    }

    return x;
}
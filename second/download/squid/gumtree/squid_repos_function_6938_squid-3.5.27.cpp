struct sockaddr_un
Ipc::PathToAddress(const String& pathAddr) {
    assert(pathAddr.size() != 0);
    struct sockaddr_un unixAddr;
    memset(&unixAddr, 0, sizeof(unixAddr));
    unixAddr.sun_family = AF_LOCAL;
    xstrncpy(unixAddr.sun_path, pathAddr.termedBuf(), sizeof(unixAddr.sun_path));
    return unixAddr;
}
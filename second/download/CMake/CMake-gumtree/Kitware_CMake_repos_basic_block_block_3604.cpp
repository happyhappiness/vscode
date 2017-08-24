{
    struct addrinfo hints, *ai;
    int error;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
#ifndef getaddrinfo
    (void)getaddrinfo;
#endif
    error = getaddrinfo("127.0.0.1", "8080", &hints, &ai);
    if (error) {
        return 1;
    }
    return 0;
}
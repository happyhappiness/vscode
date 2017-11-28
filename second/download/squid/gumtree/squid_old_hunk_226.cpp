/**** PUBLIC FUNCTIONS ****/

/*
 * start a TCP connection to the peer host on port 113
 */
void
Ident::Start(IpAddress &me, IpAddress &my_peer, IDCB * callback, void *data)
{
    IdentStateData *state;
    int fd;
    char key1[IDENT_KEY_SZ];
    char key2[IDENT_KEY_SZ];
    char key[IDENT_KEY_SZ];
    char ntoabuf[MAX_IPSTRLEN];

    me.ToURL(key1, IDENT_KEY_SZ);
    my_peer.ToURL(key2, IDENT_KEY_SZ);
    snprintf(key, IDENT_KEY_SZ, "%s,%s", key1, key2);

    if (!ident_hash) {
        Init();
    }
    if ((state = (IdentStateData *)hash_lookup(ident_hash, key)) != NULL) {
        ClientAdd(state, callback, data);
        return;
    }

    IpAddress addr = me;
    addr.SetPort(0); // NP: use random port for secure outbound to IDENT_PORT

    fd = comm_open_listener(SOCK_STREAM,
                            IPPROTO_TCP,
                            addr,
                            COMM_NONBLOCKING,
                            "ident");

    if (fd == COMM_ERROR) {
        /* Failed to get a local socket */
        callback(NULL, data);
        return;
    }

    CBDATA_INIT_TYPE(IdentStateData);
    state = cbdataAlloc(IdentStateData);
    state->hash.key = xstrdup(key);
    state->fd = fd;
    state->me = me;
    state->my_peer = my_peer;
    ClientAdd(state, callback, data);
    hash_join(ident_hash, &state->hash);
    comm_add_close_handler(fd, Ident::Close, state);
    commSetTimeout(fd, Ident::TheConfig.timeout, Ident::Timeout, state);
    state->my_peer.NtoA(ntoabuf,MAX_IPSTRLEN);
    commConnectStart(fd, ntoabuf, IDENT_PORT, Ident::ConnectDone, state);
}

void
Ident::Init(void)
{
    if (ident_hash) {

void
ConnStateData::postHttpsAccept()
{
    if (port->flags.tunnelSslBumping) {
        debugs(33, 5, "accept transparent connection: " << clientConnection);

        if (!Config.accessList.ssl_bump) {
            httpsSslBumpAccessCheckDone(ACCESS_DENIED, this);
            return;
        }

        // Create a fake HTTP request for ssl_bump ACL check,
        // using tproxy/intercept provided destination IP and port.
        HttpRequest *request = new HttpRequest();
        static char ip[MAX_IPSTRLEN];
        assert(clientConnection->flags & (COMM_TRANSPARENT | COMM_INTERCEPTION));
        request->SetHost(clientConnection->local.toStr(ip, sizeof(ip)));
        request->port = clientConnection->local.port();
        request->myportname = port->name;

        ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(Config.accessList.ssl_bump, request, NULL);
        acl_checklist->src_addr = clientConnection->remote;
        acl_checklist->my_addr = port->s;
        acl_checklist->nonBlockingCheck(httpsSslBumpAccessCheckDone, this);
        return;
    } else {
        SSL_CTX *sslContext = port->staticSslContext.get();
        httpsEstablish(this, sslContext, Ssl::bumpNone);
    }
}
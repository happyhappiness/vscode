void
ConnStateData::startPeekAndSpliceDone()
{
    // This is the Step2 of the SSL bumping
    assert(sslServerBump);
    if (sslServerBump->step == Ssl::bumpStep1) {
        sslServerBump->step = Ssl::bumpStep2;
        // Run a accessList check to check if want to splice or continue bumping

        ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(Config.accessList.ssl_bump, sslServerBump->request.getRaw(), NULL);
        //acl_checklist->src_addr = params.conn->remote;
        //acl_checklist->my_addr = s->s;
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpNone));
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpClientFirst));
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpServerFirst));
        acl_checklist->nonBlockingCheck(httpsSslBumpStep2AccessCheckDone, this);
        return;
    }

    FwdState::fwdStart(clientConnection, sslServerBump->entry, sslServerBump->request.getRaw());
}
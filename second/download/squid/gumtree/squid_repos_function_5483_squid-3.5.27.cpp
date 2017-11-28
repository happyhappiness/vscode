SBuf
Ftp::Gateway::ftpRealm()
{
    SBuf realm;

    /* This request is not fully authenticated */
    realm.appendf("FTP %s ", user);
    if (!request)
        realm.append("unknown", 7);
    else {
        realm.append(request->GetHost());
        if (request->port != 21)
            realm.appendf(" port %d", request->port);
    }
    return realm;
}
Ftp::MasterState &
Ftp::Relay::updateMaster()
{
    CbcPointer<ConnStateData> &mgr = fwd->request->clientConnectionManager;
    if (mgr.valid()) {
        if (Ftp::Server *srv = dynamic_cast<Ftp::Server*>(mgr.get()))
            return *srv->master;
    }
    // this code will not be necessary once the master is inside MasterXaction
    debugs(9, 3, "our server side is gone: " << mgr);
    static Ftp::MasterState Master;
    Master = Ftp::MasterState();
    return Master;
}
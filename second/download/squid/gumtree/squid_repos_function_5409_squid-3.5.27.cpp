void
Ftp::Relay::readGreeting()
{
    assert(!master().clientReadGreeting);

    switch (ctrl.replycode) {
    case 220:
        updateMaster().clientReadGreeting = true;
        if (serverState() == fssBegin)
            serverState(fssConnected);

        // Do not forward server greeting to the user because our FTP Server
        // has greeted the user already. Also, an original origin greeting may
        // confuse a user that has changed the origin mid-air.

        start();
        break;
    case 120:
        if (NULL != ctrl.message)
            debugs(9, DBG_IMPORTANT, "FTP server is busy: " << ctrl.message->key);
        forwardPreliminaryReply(&Ftp::Relay::scheduleReadControlReply);
        break;
    default:
        failed();
        break;
    }
}
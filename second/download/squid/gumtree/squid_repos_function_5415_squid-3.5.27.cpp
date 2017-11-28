void
Ftp::Relay::readDataReply()
{
    assert(serverState() == fssHandleDataRequest ||
           serverState() == fssHandleUploadRequest);

    if (ctrl.replycode == 125 || ctrl.replycode == 150) {
        if (serverState() == fssHandleDataRequest)
            forwardPreliminaryReply(&Ftp::Relay::startDataDownload);
        else // serverState() == fssHandleUploadRequest
            forwardPreliminaryReply(&Ftp::Relay::startDataUpload);
    } else
        forwardReply();
}
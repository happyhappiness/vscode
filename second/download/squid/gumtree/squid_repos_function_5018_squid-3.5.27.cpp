void
Ftp::Server::replyDataWritingCheckpoint()
{
    switch (getCurrentContext()->socketState()) {
    case STREAM_NONE:
        debugs(33, 3, "Keep going");
        getCurrentContext()->pullData();
        return;
    case STREAM_COMPLETE:
        debugs(33, 3, "FTP reply data transfer successfully complete");
        userDataCompletionCheckpoint(226);
        break;
    case STREAM_UNPLANNED_COMPLETE:
        debugs(33, 3, "FTP reply data transfer failed: STREAM_UNPLANNED_COMPLETE");
        userDataCompletionCheckpoint(451);
        break;
    case STREAM_FAILED:
        userDataCompletionCheckpoint(451);
        debugs(33, 3, "FTP reply data transfer failed: STREAM_FAILED");
        break;
    default:
        fatal("unreachable code");
    }
}
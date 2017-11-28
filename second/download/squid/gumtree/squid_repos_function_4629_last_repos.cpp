void
Ftp::Server::wroteReplyData(const CommIoCbParams &io)
{
    if (io.flag == Comm::ERR_CLOSING)
        return;

    if (io.flag != Comm::OK) {
        debugs(33, 3, "FTP reply data writing failed: " << xstrerr(io.xerrno));
        userDataCompletionCheckpoint(426);
        return;
    }

    assert(pipeline.front()->http);
    pipeline.front()->http->out.size += io.size;
    replyDataWritingCheckpoint();
}
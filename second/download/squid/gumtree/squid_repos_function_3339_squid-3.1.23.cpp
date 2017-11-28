int
clientReplyContext::storeOKTransferDone() const
{
    if (http->out.offset >= http->storeEntry()->objectLen() - headers_sz) {
        debugs(88,3,HERE << "storeOKTransferDone " <<
               " out.offset=" << http->out.offset <<
               " objectLen()=" << http->storeEntry()->objectLen() <<
               " headers_sz=" << headers_sz);
        return 1;
    }

    return 0;
}
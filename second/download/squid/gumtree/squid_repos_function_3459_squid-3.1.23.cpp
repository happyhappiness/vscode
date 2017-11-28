clientStream_status_t
ClientSocketContext::socketState()
{
    switch (clientStreamStatus(getTail(), http)) {

    case STREAM_NONE:
        /* check for range support ending */

        if (http->request->range) {
            /* check: reply was parsed and range iterator was initialized */
            assert(http->range_iter.valid);
            /* filter out data according to range specs */

            if (!canPackMoreRanges()) {
                debugs(33, 5, HERE << "Range request at end of returnable " <<
                       "range sequence on FD " << fd());

                if (http->request->flags.proxy_keepalive)
                    return STREAM_COMPLETE;
                else
                    return STREAM_UNPLANNED_COMPLETE;
            }
        } else if (reply && reply->content_range) {
            /* reply has content-range, but Squid is not managing ranges */
            const int64_t &bytesSent = http->out.offset;
            const int64_t &bytesExpected = reply->content_range->spec.length;

            debugs(33, 7, HERE << "body bytes sent vs. expected: " <<
                   bytesSent << " ? " << bytesExpected << " (+" <<
                   reply->content_range->spec.offset << ")");

            // did we get at least what we expected, based on range specs?

            if (bytesSent == bytesExpected) { // got everything
                if (http->request->flags.proxy_keepalive)
                    return STREAM_COMPLETE;
                else
                    return STREAM_UNPLANNED_COMPLETE;
            }

            // The logic below is not clear: If we got more than we
            // expected why would persistency matter? Should not this
            // always be an error?
            if (bytesSent > bytesExpected) { // got extra
                if (http->request->flags.proxy_keepalive)
                    return STREAM_COMPLETE;
                else
                    return STREAM_UNPLANNED_COMPLETE;
            }

            // did not get enough yet, expecting more
        }

        return STREAM_NONE;

    case STREAM_COMPLETE:
        return STREAM_COMPLETE;

    case STREAM_UNPLANNED_COMPLETE:
        return STREAM_UNPLANNED_COMPLETE;

    case STREAM_FAILED:
        return STREAM_FAILED;
    }

    fatal ("unreachable code\n");
    return STREAM_NONE;
}
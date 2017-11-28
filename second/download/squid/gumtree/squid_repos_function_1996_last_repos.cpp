static void
redirectHandleReply(void *data, const Helper::Reply &reply)
{
    RedirectStateData *r = static_cast<RedirectStateData *>(data);
    debugs(61, 5, HERE << "reply=" << reply);

    // XXX: This function is now kept only to check for and display the garbage use-case
    // and to map the old helper response format(s) into new format result code and key=value pairs
    // it can be removed when the helpers are all updated to the normalized "OK/ERR kv-pairs" format

    if (reply.result == Helper::Unknown) {
        // BACKWARD COMPATIBILITY 2012-06-15:
        // Some nasty old helpers send back the entire input line including extra format keys.
        // This is especially bad for simple perl search-replace filter scripts.
        //
        // * trim all but the first word off the response.
        // * warn once every 50 responses that this will stop being fixed-up soon.
        //
        if (reply.other().hasContent()) {
            const char * res = reply.other().content();
            size_t replySize = 0;
            if (const char *t = strchr(res, ' ')) {
                static int warn = 0;
                debugs(61, (!(warn++%50)? DBG_CRITICAL:2), "UPGRADE WARNING: URL rewriter reponded with garbage '" << t <<
                       "'. Future Squid will treat this as part of the URL.");
                replySize = t - res;
            } else
                replySize = reply.other().contentSize();

            // if we still have anything in other() after all that
            // parse it into status=, url= and rewrite-url= keys
            if (replySize) {
                /* 2012-06-28: This cast is due to URL::parse() truncating too-long URLs itself.
                 * At this point altering the helper buffer in that way is not harmful, but annoying.
                 * When Bug 1961 is resolved and URL::parse has a const API, this needs to die.
                 */
                MemBuf replyBuffer;
                replyBuffer.init(replySize, replySize);
                replyBuffer.append(reply.other().content(), reply.other().contentSize());
                char * result = replyBuffer.content();

                Helper::Reply newReply;
                // BACKWARD COMPATIBILITY 2012-06-15:
                // We got Helper::Unknown reply result but new
                // RedirectStateData handlers require Helper::Okay,
                // else will drop the helper reply
                newReply.result = Helper::Okay;
                newReply.notes.append(&reply.notes);

                // check and parse for obsoleted Squid-2 urlgroup feature
                if (*result == '!') {
                    static int urlgroupWarning = 0;
                    if (!urlgroupWarning++)
                        debugs(85, DBG_IMPORTANT, "UPGRADE WARNING: URL rewriter using obsolete Squid-2 urlgroup feature needs updating.");
                    if (char *t = strchr(result+1, '!')) {
                        *t = '\0';
                        newReply.notes.add("urlgroup", result+1);
                        result = t + 1;
                    }
                }

                const Http::StatusCode status = static_cast<Http::StatusCode>(atoi(result));

                if (status == Http::scMovedPermanently
                        || status == Http::scFound
                        || status == Http::scSeeOther
                        || status == Http::scPermanentRedirect
                        || status == Http::scTemporaryRedirect) {

                    if (const char *t = strchr(result, ':')) {
                        char statusBuf[4];
                        snprintf(statusBuf, sizeof(statusBuf),"%3u",status);
                        newReply.notes.add("status", statusBuf);
                        ++t;
                        // TODO: validate the URL produced here is RFC 2616 compliant URI
                        newReply.notes.add("url", t);
                    } else {
                        debugs(85, DBG_CRITICAL, "ERROR: URL-rewrite produces invalid " << status << " redirect Location: " << result);
                    }
                } else {
                    // status code is not a redirect code (or does not exist)
                    // treat as a re-write URL request
                    // TODO: validate the URL produced here is RFC 2616 compliant URI
                    if (*result)
                        newReply.notes.add("rewrite-url", result);
                }

                void *cbdata;
                if (cbdataReferenceValidDone(r->data, &cbdata))
                    r->handler(cbdata, newReply);

                delete r;
                return;
            }
        }
    }

    void *cbdata;
    if (cbdataReferenceValidDone(r->data, &cbdata))
        r->handler(cbdata, reply);

    delete r;
}
    } else if (!srv->flags.closing && !srv->flags.reserved && !srv->stats.pending) {
        srv->closeWritePipeSafely(srv->parent->id_name);
        return;
    }
}

void
helper_server::checkForTimedOutRequests(bool const retry)
{
    assert(parent->childs.concurrency);
    while(!requests.empty() && requests.front()->request.timedOut(parent->timeout)) {
        Helper::Xaction *r = requests.front();
        RequestIndex::iterator it;
        it = requestsIndex.find(r->request.Id);
        assert(it != requestsIndex.end());
        requestsIndex.erase(it);
        requests.pop_front();
        debugs(84, 2, "Request " << r->request.Id << " timed-out, remove it from queue");
        void *cbdata;
        bool retried = false;
        if (retry && r->request.retries < MAX_RETRIES && cbdataReferenceValid(r->request.data)) {
            debugs(84, 2, "Retry request " << r->request.Id);
            ++r->request.retries;
            parent->submitRequest(r);
            retried = true;
        } else if (cbdataReferenceValidDone(r->request.data, &cbdata)) {
            if (!parent->onTimedOutResponse.isEmpty()) {
                if (r->reply.accumulate(parent->onTimedOutResponse.rawContent(), parent->onTimedOutResponse.length()))
                    r->reply.finalize();
                else
                    r->reply.result = Helper::TimedOut;
                r->request.callback(cbdata, r->reply);
            } else {
                r->reply.result = Helper::TimedOut;
                r->request.callback(cbdata, r->reply);
            }
        }
        --stats.pending;
        ++stats.timedout;
        ++parent->stats.timedout;
        if (!retried)
            delete r;
    }
}

void
helper_server::requestTimeout(const CommTimeoutCbParams &io)
{
    debugs(26, 3, HERE << io.conn);
    helper_server *srv = static_cast<helper_server *>(io.data);

    if (!cbdataReferenceValid(srv))
        return;

    srv->checkForTimedOutRequests(srv->parent->retryTimedOut);

    debugs(84, 3, HERE << io.conn << " establish new helper_server::requestTimeout");
    AsyncCall::Pointer timeoutCall = commCbCall(84, 4, "helper_server::requestTimeout",
                                     CommTimeoutCbPtrFun(helper_server::requestTimeout, srv));

    const int timeSpent = srv->requests.empty() ? 0 : (squid_curtime - srv->requests.front()->request.dispatch_time.tv_sec);
    const int timeLeft = max(1, (static_cast<int>(srv->parent->timeout) - timeSpent));

    commSetConnTimeout(io.conn, timeLeft, timeoutCall);
}


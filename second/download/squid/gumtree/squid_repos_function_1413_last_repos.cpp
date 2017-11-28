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
Helper::Xaction *
helper_server::popRequest(int request_number)
{
    Helper::Xaction *r = nullptr;
    helper_server::RequestIndex::iterator it;
    if (parent->childs.concurrency) {
        // If concurency supported retrieve request from ID
        it = requestsIndex.find(request_number);
        if (it != requestsIndex.end()) {
            r = *(it->second);
            requests.erase(it->second);
            requestsIndex.erase(it);
        }
    } else if(!requests.empty()) {
        // Else get the first request from queue, if any
        r = requests.front();
        requests.pop_front();
    }

    return r;
}
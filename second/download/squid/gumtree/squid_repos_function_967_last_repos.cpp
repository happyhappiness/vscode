Http::StreamPointer
Pipeline::back() const
{
    if (requests.empty()) {
        debugs(33, 3, "Pipeline " << (void*)this << " empty");
        return Http::StreamPointer();
    }

    debugs(33, 3, "Pipeline " << (void*)this << " back " << requests.back());
    return requests.back();
}
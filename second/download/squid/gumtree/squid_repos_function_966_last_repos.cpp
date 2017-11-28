Http::StreamPointer
Pipeline::front() const
{
    if (requests.empty()) {
        debugs(33, 3, "Pipeline " << (void*)this << " empty");
        return Http::StreamPointer();
    }

    debugs(33, 3, "Pipeline " << (void*)this << " front " << requests.front());
    return requests.front();
}
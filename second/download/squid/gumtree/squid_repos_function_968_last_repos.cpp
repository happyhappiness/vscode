void
Pipeline::terminateAll(int xerrno)
{
    while (!requests.empty()) {
        Http::StreamPointer context = requests.front();
        debugs(33, 3, "Pipeline " << (void*)this << " notify(" << xerrno << ") " << context);
        context->noteIoError(xerrno);
        context->finished();  // cleanup and self-deregister
        assert(context != requests.front());
    }
}
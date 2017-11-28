void
Pipeline::add(const Http::StreamPointer &c)
{
    requests.push_back(c);
    ++nrequests;
    debugs(33, 3, "Pipeline " << (void*)this << " add request " << nrequests << ' ' << c);
}
void
Adaptation::Ecap::Host::noteService(const libecap::weak_ptr<libecap::adapter::Service> &weak)
{
    Must(!weak.expired());
    RegisterAdapterService(weak.lock());
}
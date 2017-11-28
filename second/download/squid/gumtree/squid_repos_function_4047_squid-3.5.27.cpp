void
Adaptation::Ecap::Host::noteVersionedService(const char *vGiven, const libecap::weak_ptr<libecap::adapter::Service> &weak)
{
    /*
     * Check that libecap used to build the service is compatible with ours.
     * This has to be done using vGiven string and not Service object itself
     * because dereferencing a Service pointer coming from an unsupported
     * version is unsafe.
     */
    if (SupportedVersion(vGiven, "eCAP service built")) {
        Must(!weak.expired());
        RegisterAdapterService(weak.lock());
    }
}
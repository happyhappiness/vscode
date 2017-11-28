/// call back with a possibly nil group; the job ends here because all failures
/// at this point are fatal to the access check process
void
Adaptation::AccessCheck::callBack(const ServiceGroupPointer &g)
{
    debugs(93,3, HERE << g);

    void *validated_cbdata;
    if (cbdataReferenceValidDone(callback_data, &validated_cbdata)) {
        callback(g, validated_cbdata);
    }
    mustStop("done"); // called back or will never be able to call back
}

Adaptation::ServiceGroupPointer
Adaptation::AccessCheck::topGroup() const
{

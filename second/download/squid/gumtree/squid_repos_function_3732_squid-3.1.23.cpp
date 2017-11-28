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
void HttpReply::reset()
{

    // reset should not reset the protocol; could have made protoPrefix a
    // virtual function instead, but it is not clear whether virtual methods
    // are allowed with MEMPROXY_CLASS() and whether some cbdata void*
    // conversions are not going to kill virtual tables
    const String pfx = protoPrefix;
    clean();
    init();
    protoPrefix = pfx;
}
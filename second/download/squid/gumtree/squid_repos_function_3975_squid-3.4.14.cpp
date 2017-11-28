static int
SquidLogLevel(libecap::LogVerbosity lv)
{
    if (lv.critical())
        return DBG_CRITICAL; // is it a good idea to ignore other flags?

    if (lv.large())
        return DBG_DATA; // is it a good idea to ignore other flags?

    if (lv.application())
        return DBG_IMPORTANT; // is it a good idea to ignore other flags?

    return 2 + 2*lv.debugging() + 3*lv.operation() + 2*lv.xaction();
}
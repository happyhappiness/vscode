bool
StoreMeta::validLength(int aLength) const
{
    if (!IntRange (MinimumTLVLength, MaximumTLVLength).includes(aLength)) {
        debugs(20, DBG_CRITICAL, "storeSwapMetaUnpack: insane length (" << aLength << ")!");
        return false;
    }

    return true;
}
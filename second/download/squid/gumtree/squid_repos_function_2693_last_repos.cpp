bool
internalCheck(const SBuf &urlPath)
{
    static const SBuf InternalPfx("/squid-internal-");
    return urlPath.startsWith(InternalPfx);
}
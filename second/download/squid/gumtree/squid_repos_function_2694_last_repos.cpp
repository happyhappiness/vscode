bool
internalStaticCheck(const SBuf &urlPath)
{
    static const SBuf InternalStaticPfx("/squid-internal-static");
    return urlPath.startsWith(InternalStaticPfx);
}
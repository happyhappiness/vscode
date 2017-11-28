SBuf
Ipc::Mem::Segment::Name(const SBuf &prefix, const char *suffix)
{
    SBuf result = prefix;
    result.append("_");
    result.append(suffix);
    return result;
}
SBuf&
SBuf::append(const SBuf &S)
{
    const Locker blobKeeper(this, S.buf());
    return lowAppend(S.buf(), S.length());
}
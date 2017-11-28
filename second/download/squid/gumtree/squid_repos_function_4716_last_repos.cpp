SBuf&
SBuf::append(const SBuf &S)
{
    if (isEmpty() && store_ == GetStorePrototype())
        return (*this = S); // optimization: avoid needless copying

    const Locker blobKeeper(this, S.buf());
    return lowAppend(S.buf(), S.length());
}
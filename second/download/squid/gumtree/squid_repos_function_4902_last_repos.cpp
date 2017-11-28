void
Http::One::Parser::unfoldMime()
{
    Http1::Tokenizer tok(mimeHeaderBlock_);
    const auto szLimit = mimeHeaderBlock_.length();
    mimeHeaderBlock_.clear();
    // prevent the mime sender being able to make append() realloc/grow multiple times.
    mimeHeaderBlock_.reserveSpace(szLimit);

    static const CharacterSet nonCRLF = (CharacterSet::CR + CharacterSet::LF).complement().rename("non-CRLF");

    while (!tok.atEnd()) {
        const SBuf all(tok.remaining());
        const auto blobLen = tok.skipAll(nonCRLF); // may not be there
        const auto crLen = tok.skipAll(CharacterSet::CR); // may not be there
        const auto lfLen = tok.skipOne(CharacterSet::LF); // may not be there

        if (lfLen && tok.skipAll(CharacterSet::WSP)) { // obs-fold!
            mimeHeaderBlock_.append(all.substr(0, blobLen));
            mimeHeaderBlock_.append(' '); // replace one obs-fold with one SP
        } else
            mimeHeaderBlock_.append(all.substr(0, blobLen + crLen + lfLen));
    }
}
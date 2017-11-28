void
Http::One::Parser::cleanMimePrefix()
{
    Http1::Tokenizer tok(mimeHeaderBlock_);
    while (tok.skipOne(RelaxedDelimiterCharacters())) {
        (void)tok.skipAll(LineCharacters()); // optional line content
        // LF terminator is required.
        // trust headersEnd() to ensure that we have at least one LF
        (void)tok.skipOne(CharacterSet::LF);
    }

    // If mimeHeaderBlock_ had just whitespace line(s) followed by CRLF,
    // then we skipped everything, including that terminating LF.
    // Restore the terminating CRLF if needed.
    if (tok.atEnd())
        mimeHeaderBlock_ = Http1::CrLf();
    else
        mimeHeaderBlock_ = tok.remaining();
    // now mimeHeaderBlock_ has 0+ fields followed by the LF terminator
}
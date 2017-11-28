void
ESIContext::parseOneBuffer()
{
    assert (buffered.getRaw());

    debugs (86,9,"ESIContext::parseOneBuffer: " << buffered->len << " bytes");
    bool lastBlock = buffered->next.getRaw() == NULL && flags.finishedtemplate ? true : false;

    if (! parserState.theParser->parse(buffered->buf, buffered->len, lastBlock)) {
        setError();
        char tempstr[1024];
        snprintf (tempstr, 1023, "esiProcess: Parse error at line %ld:\n%s\n",
                  parserState.theParser->lineNumber(),
                  parserState.theParser->errorString());
        debugs(86, DBG_CRITICAL, "" << tempstr << "");

        setErrorMessage(tempstr);

        assert (flags.error);

        return;
    }

    if (flags.error) {
        setError();
        return;
    }

    ESISegment::Pointer temp = buffered;
    buffered = temp->next;
}
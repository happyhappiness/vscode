void
ESIContext::parse()
{
    if (!parserState.stackdepth) {
        debugs(86, 5, "empty parser stack, inserting the top level node");
        assert (tree.getRaw());
        parserState.stack[parserState.stackdepth] = tree;
        ++parserState.stackdepth;
    }

    if (rep != NULL && !parserState.inited())
        parserState.init(this);

    /* we have data */
    if (buffered.getRaw()) {
        parserState.parsing = 1;
        /* we don't keep any data around */

        PROF_start(esiParsing);

        while (buffered.getRaw() && !flags.error)
            parseOneBuffer();

        PROF_stop(esiParsing);

        /* Tel the read code to allocate a new buffer */
        incoming = NULL;

        parserState.parsing = 0;
    }
}
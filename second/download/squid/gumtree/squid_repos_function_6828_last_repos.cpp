char *
ESIVarState::extractChar ()
{
    if (!input.getRaw())
        fatal ("Attempt to extract variable state with no data fed in \n");

    doIt();

    char *rv = output->listToChar();

    ESISegmentFreeList (output);

    debugs(86, 6, "ESIVarStateExtractList: Extracted char");

    return rv;
}
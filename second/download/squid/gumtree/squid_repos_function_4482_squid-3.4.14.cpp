wordlist *
ACLNoteData::dump()
{
    wordlist *W = NULL;
    wordlistAdd(&W, name.termedBuf());
    wordlist * dumpR = values->dump();
    wordlistAddWl(&W, dumpR);
    wordlistDestroy(&dumpR);
    return W;
}
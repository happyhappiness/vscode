void
ESIContext::getCachedAST()
{
    if (cachedASTInUse)
        return;

    assert (hasCachedAST());

    assert (varState);

    parserState.popAll();

    tree = http->storeEntry()->cachedESITree->makeUsable (this, *varState);

    cachedASTInUse = true;
}
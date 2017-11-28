void
ESIContext::updateCachedAST()
{
    assert (http);
    assert (http->storeEntry());

    if (hasCachedAST()) {
        debugs(86, 5, "ESIContext::updateCachedAST: not updating AST cache for entry " <<
               http->storeEntry() << " from ESI Context " << this <<
               " as there is already a cached AST.");

        return;
    }

    ESIElement::Pointer treeToCache = tree->makeCacheable();
    debugs(86, 5, "ESIContext::updateCachedAST: Updating AST cache for entry " <<
           http->storeEntry() << " with current value " <<
           http->storeEntry()->cachedESITree.getRaw() << " to new value " <<
           treeToCache.getRaw());

    if (http->storeEntry()->cachedESITree.getRaw())
        http->storeEntry()->cachedESITree->finish();

    http->storeEntry()->cachedESITree = treeToCache;

    treeToCache = NULL;
}
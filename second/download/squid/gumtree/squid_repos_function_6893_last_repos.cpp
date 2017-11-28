bool
ESIContext::hasCachedAST() const
{
    assert (http);
    assert (http->storeEntry());

    if (http->storeEntry()->cachedESITree.getRaw()) {
        debugs(86, 5, "ESIContext::hasCachedAST: " << this <<
               " - Cached AST present in store entry " << http->storeEntry() << ".");
        return true;
    } else {
        debugs(86, 5, "ESIContext::hasCachedAST: " << this <<
               " - Cached AST not present in store entry " << http->storeEntry() << ".");
        return false;
    }
}
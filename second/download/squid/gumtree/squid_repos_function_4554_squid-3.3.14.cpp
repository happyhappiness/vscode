bool
ACLChecklist::matchNodes(const ACLList * head, bool const fast)
{
    assert(!finished());

    for (const ACLList *node = head; node; node = node->next) {

        const NodeMatchingResult resultBeforeAsync = matchNode(*node, fast);

        if (resultBeforeAsync == nmrMatch)
            continue;

        if (resultBeforeAsync == nmrMismatch || resultBeforeAsync == nmrFinished)
            return false;

        assert(resultBeforeAsync == nmrNeedsAsync);

        // Ideally, this should be inside match() itself, but that requires
        // prohibiting slow ACLs in options that do not support them.
        // TODO: rename to maybeStartAsync()?
        checkForAsync();

        // Some match() code claims that an async lookup is needed, but then
        // fails to start an async lookup when given a chance. We catch such
        // cases here and call matchNode() again, hoping that some cached data
        // prevents us from going async again.
        // This is inefficient and ugly, but fixing all match() code, including
        // the code it calls, such as ipcache_nbgethostbyname(), takes time.
        if (!asyncInProgress()) { // failed to start an async operation

            if (finished()) {
                debugs(28, 3, HERE << this << " finished after failing to go async: " << currentAnswer());
                return false; // an exceptional case
            }

            const NodeMatchingResult resultAfterAsync = matchNode(*node, true);
            // the second call disables slow checks so we cannot go async again
            assert(resultAfterAsync != nmrNeedsAsync);
            if (resultAfterAsync == nmrMatch)
                continue;

            assert(resultAfterAsync == nmrMismatch || resultAfterAsync == nmrFinished);
            return false;
        }

        assert(!finished()); // async operation is truly asynchronous
        debugs(28, 3, HERE << this << " awaiting async operation");
        return false;
    }

    debugs(28, 3, HERE << this << " success: all ACLs matched");
    return true;
}
        whole = oldWhole;
    } else if (oldNode) {
        // this acl saw a single line before; create a new OR inner node

        MemBuf wholeCtx;
        wholeCtx.init();
        wholeCtx.appendf("(%s lines)", name);
        wholeCtx.terminate();

        Acl::OrNode *newWhole = new Acl::OrNode;
        newWhole->context(wholeCtx.content(), oldNode->cfgline);
        newWhole->add(oldNode); // old (i.e. first) line
        nodes.front() = whole = newWhole;

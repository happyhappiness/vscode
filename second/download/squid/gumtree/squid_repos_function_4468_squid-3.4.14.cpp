void
Acl::AllOf::parse()
{
    Acl::InnerNode *whole = NULL;
    ACL *oldNode = empty() ? NULL : nodes.front();

    // optimization: this logic reduces subtree hight (number of tree levels)
    if (Acl::OrNode *oldWhole = dynamic_cast<Acl::OrNode*>(oldNode)) {
        // this acl saw multiple lines before; add another one to the old node
        whole = oldWhole;
    } else if (oldNode) {
        // this acl saw a single line before; create a new OR inner node

        MemBuf wholeCtx;
        wholeCtx.init();
        wholeCtx.Printf("(%s lines)", name);
        wholeCtx.terminate();

        Acl::OrNode *newWhole = new Acl::OrNode;
        newWhole->context(wholeCtx.content(), oldNode->cfgline);
        newWhole->add(oldNode); // old (i.e. first) line
        nodes.front() = whole = newWhole;
    } else {
        // this is the first line for this acl; just use it as is
        whole = this;
    }

    assert(whole);
    const int lineId = whole->childrenCount() + 1;

    MemBuf lineCtx;
    lineCtx.init();
    lineCtx.Printf("(%s line #%d)", name, lineId);
    lineCtx.terminate();

    Acl::AndNode *line = new AndNode;
    line->context(lineCtx.content(), config_input_line);
    line->lineParse();

    whole->add(line);
}
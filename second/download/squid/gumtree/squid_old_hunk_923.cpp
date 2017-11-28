
    assert(whole);
    const int lineId = whole->childrenCount() + 1;

    MemBuf lineCtx;
    lineCtx.init();
    lineCtx.Printf("(%s line #%d)", name, lineId);
    lineCtx.terminate();

    Acl::AndNode *line = new AndNode;
    line->context(lineCtx.content(), config_input_line);
    line->lineParse();


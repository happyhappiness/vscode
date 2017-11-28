void
ESIContext::addLiteral (const char *s, int len)
{
    /* handle any skipped data */
    assert (len);
    debugs(86, 5, "literal length is " << len);
    /* give a literal to the current element */
    assert (parserState.stackdepth <11);
    ESIElement::Pointer element (new esiLiteral (this, s, len));

    if (!parserState.top()->addElement(element)) {
        debugs(86, DBG_IMPORTANT, "ESIContext::addLiteral: failed to add esi node, probable error in ESI template");
        flags.error = 1;
    }
}
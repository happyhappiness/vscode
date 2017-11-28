void
ESIContext::addStackElement (ESIElement::Pointer element)
{
    /* Put on the stack to allow skipping of 'invalid' markup */
    assert (parserState.stackdepth <11);
    assert (!failed());
    debugs(86, 5, "ESIContext::addStackElement: About to add ESI Node " << element.getRaw());

    if (!parserState.top()->addElement(element)) {
        debugs(86, 1, "ESIContext::addStackElement: failed to add esi node, probable error in ESI template");
        flags.error = 1;
    } else {
        /* added ok, push onto the stack */
        parserState.stack[parserState.stackdepth++] = element;
    }
}
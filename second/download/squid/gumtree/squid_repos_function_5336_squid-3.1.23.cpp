void
ESIContext::end(const char *el)
{
    unsigned int ellen = strlen (el);
    char localbuf [HTTP_REQBUF_SZ];
    char *position;

    if (flags.error)
        /* waiting for expat to finish the buffer we gave it */
        return;

    switch (ESIElement::IdentifyElement (el)) {

    case ESIElement::ESI_ELEMENT_NONE:
        assert (ellen < sizeof (localbuf)); /* prevent unexpected overruns. */
        /* Add elements we aren't interested in */
        localbuf[0] = '<';
        localbuf[1] = '/';
        assert (xstrncpy (&localbuf[2], el, sizeof(localbuf) - 3));
        position = localbuf + strlen (localbuf);
        *position++ = '>';
        *position = '\0';
        addLiteral (localbuf, position - localbuf);
        break;

    case ESIElement::ESI_ELEMENT_COMMENT:

    case ESIElement::ESI_ELEMENT_INCLUDE:

    case ESIElement::ESI_ELEMENT_REMOVE:

    case ESIElement::ESI_ELEMENT_TRY:

    case ESIElement::ESI_ELEMENT_ATTEMPT:

    case ESIElement::ESI_ELEMENT_EXCEPT:

    case ESIElement::ESI_ELEMENT_VARS:

    case ESIElement::ESI_ELEMENT_CHOOSE:

    case ESIElement::ESI_ELEMENT_WHEN:

    case ESIElement::ESI_ELEMENT_OTHERWISE:

    case ESIElement::ESI_ELEMENT_ASSIGN:
        /* pop of the stack */
        parserState.stack[--parserState.stackdepth] = NULL;
        break;
    }
}
void
ESIContext::start(const char *el, const char **attr, size_t attrCount)
{
    int i;
    unsigned int ellen = strlen (el);
    char localbuf [HTTP_REQBUF_SZ];
    ESIElement::Pointer element;
    int specifiedattcount = attrCount * 2;
    char *position;
    Must(ellen < sizeof(localbuf)); /* prevent unexpected overruns. */

    debugs(86, 5, "ESIContext::Start: element '" << el << "' with " << specifiedattcount << " tags");

    if (failed())
        /* waiting for expat to finish the buffer we gave it */
        return;

    switch (ESIElement::IdentifyElement (el)) {

    case ESIElement::ESI_ELEMENT_NONE:
        /* Spit out elements we aren't interested in */
        localbuf[0] = '<';
        localbuf[1] = '\0';
        xstrncpy(&localbuf[1], el, sizeof(localbuf) - 2);
        position = localbuf + strlen (localbuf);

        for (i = 0; i < specifiedattcount && attr[i]; i += 2) {
            Must(static_cast<size_t>(position - localbuf) < sizeof(localbuf) - 1);
            *position = ' ';
            ++position;
            /* TODO: handle thisNode gracefully */
            xstrncpy(position, attr[i], sizeof(localbuf) - (position - localbuf));
            position += strlen (position);
            Must(static_cast<size_t>(position - localbuf) < sizeof(localbuf) - 2);
            *position = '=';
            ++position;
            *position = '\"';
            ++position;
            const char *chPtr = attr[i + 1];
            char ch;
            while ((ch = *chPtr++) != '\0') {
                if (ch == '\"') {
                    Must(static_cast<size_t>(position - localbuf) < sizeof(localbuf) - 6);
                    xstrncpy(position, "&quot;", sizeof(localbuf) - (position-localbuf));
                    position += 6;
                } else {
                    Must(static_cast<size_t>(position - localbuf) < sizeof(localbuf) - 1);
                    *position = ch;
                    ++position;
                }
            }
            Must(static_cast<size_t>(position - localbuf) < sizeof(localbuf) - 1);
            *position = '\"';
            ++position;
        }

        Must(static_cast<size_t>(position - localbuf) < sizeof(localbuf) - 2);
        *position = '>';
        ++position;
        *position = '\0';

        addLiteral (localbuf, position - localbuf);
        debugs(86, 5, "esi stack depth " << parserState.stackdepth);
        return;
        break;

    case ESIElement::ESI_ELEMENT_COMMENT:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new esiComment ();
        break;

    case ESIElement::ESI_ELEMENT_INCLUDE:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new ESIInclude (parserState.top().getRaw(), specifiedattcount, attr, this);
        break;

    case ESIElement::ESI_ELEMENT_REMOVE:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = esiRemoveNew ();
        break;

    case ESIElement::ESI_ELEMENT_TRY:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new esiTry (parserState.top().getRaw());
        break;

    case ESIElement::ESI_ELEMENT_ATTEMPT:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new esiAttempt (parserState.top().getRaw());
        break;

    case ESIElement::ESI_ELEMENT_EXCEPT:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new esiExcept (parserState.top().getRaw());
        break;

    case ESIElement::ESI_ELEMENT_VARS:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new ESIVar (parserState.top().getRaw());
        break;

    case ESIElement::ESI_ELEMENT_CHOOSE:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new esiChoose (parserState.top().getRaw());
        break;

    case ESIElement::ESI_ELEMENT_WHEN:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new esiWhen (parserState.top().getRaw(), specifiedattcount, attr, varState);
        break;

    case ESIElement::ESI_ELEMENT_OTHERWISE:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new esiOtherwise (parserState.top().getRaw());
        break;

    case ESIElement::ESI_ELEMENT_ASSIGN:
        /* Put on the stack to allow skipping of 'invalid' markup */
        element = new ESIAssign (parserState.top().getRaw(), specifiedattcount, attr, this);
        break;
    }

    addStackElement(element);

    debugs(86, 5, "esi stack depth " << parserState.stackdepth);

}
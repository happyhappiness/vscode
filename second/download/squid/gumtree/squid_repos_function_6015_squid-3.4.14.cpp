ESIElement::ESIElementType_t
ESIElement::IdentifyElement (const char *el)
{
    int offset = 0;
    assert (el);

    if (strlen (el) < 5)
        return ESI_ELEMENT_NONE;

    if (!strncmp (el, "esi:", 4))
        offset = 4;
    else if (!strncmp (el, "http://www.edge-delivery.org/esi/1.0|", 37))
        offset = 37;
    else
        return ESI_ELEMENT_NONE;

    if (!strncmp (el + offset, "otherwise", 9))
        return ESI_ELEMENT_OTHERWISE;

    if (!strncmp (el + offset, "comment", 7))
        return ESI_ELEMENT_COMMENT;

    if (!strncmp (el + offset, "include", 7))
        return ESI_ELEMENT_INCLUDE;

    if (!strncmp (el + offset, "attempt", 7))
        return ESI_ELEMENT_ATTEMPT;

    if (!strncmp (el + offset, "assign", 6))
        return ESI_ELEMENT_ASSIGN;

    if (!strncmp (el + offset, "remove", 6))
        return ESI_ELEMENT_REMOVE;

    if (!strncmp (el + offset, "except", 6))
        return ESI_ELEMENT_EXCEPT;

    if (!strncmp (el + offset, "choose", 6))
        return ESI_ELEMENT_CHOOSE;

    if (!strncmp (el + offset, "vars", 4))
        return ESI_ELEMENT_VARS;

    if (!strncmp (el + offset, "when", 4))
        return ESI_ELEMENT_WHEN;

    if (!strncmp (el + offset, "try", 3))
        return ESI_ELEMENT_TRY;

    return ESI_ELEMENT_NONE;
}
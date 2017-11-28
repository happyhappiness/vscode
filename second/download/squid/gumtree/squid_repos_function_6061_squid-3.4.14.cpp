bool
esiChoose::addElement(ESIElement::Pointer element)
{
    /* add an element to the output list */

    if (dynamic_cast<esiLiteral*>(element.getRaw())) {
        /* Swallow whitespace */
        debugs(86, 5, "esiChooseAdd: Choose " << this << " skipping whitespace " << element.getRaw());
        return true;
    }

    /* Some elements require specific parents */
    if (!(dynamic_cast<esiWhen*>(element.getRaw()) || dynamic_cast<esiOtherwise*>(element.getRaw()))) {
        debugs(86, DBG_CRITICAL, "esiChooseAdd: invalid child node for esi:choose (section 3.3)");
        return false;
    }

    if (dynamic_cast<esiOtherwise*>(element.getRaw())) {
        if (otherwise.getRaw()) {
            debugs(86, DBG_CRITICAL, "esiChooseAdd: only one otherwise node allowed for esi:choose (section 3.3)");
            return false;
        }

        otherwise = element;
    } else {
        elements.push_back (element);

        debugs (86,3, "esiChooseAdd: Added a new element, elements = " << elements.size());

        if (chosenelement == -1) {
            const esiWhen * topElement=dynamic_cast<esiWhen *>(element.getRaw());
            if (topElement && topElement->testsTrue()) {
                chosenelement = elements.size() - 1;
                debugs (86,3, "esiChooseAdd: Chose element " << elements.size());
            }
        }
    }

    return true;
}
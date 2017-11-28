bool
esiSequence::addElement (ESIElement::Pointer element)
{
    /* add an element to the output list */
    /* Some elements require specific parents */

    if (dynamic_cast<esiAttempt*>(element.getRaw()) ||
            dynamic_cast<esiExcept*>(element.getRaw())) {
        debugs(86, DBG_CRITICAL, "esiSequenceAdd: misparented Attempt or Except element (section 3.4)");
        return false;
    }

    /* Tie literals together for efficiency */
    if (elements.size() && dynamic_cast<esiLiteral*>(element.getRaw()) &&
            dynamic_cast<esiLiteral*>(elements[elements.size() - 1].getRaw())) {
        debugs(86, 5, "esiSequenceAdd: tying Literals " <<
               elements[elements.size() - 1].getRaw() << " and " <<
               element.getRaw() << " together");

        ESISegment::ListTransfer (((esiLiteral *)element.getRaw())->buffer,
                                  ((esiLiteral *)elements[elements.size() - 1].getRaw())->buffer);
        return true;
    }

    elements.push_back(element);
    debugs (86,3, "esiSequenceAdd: Added a new element, elements = " << elements.size());
    return true;
}
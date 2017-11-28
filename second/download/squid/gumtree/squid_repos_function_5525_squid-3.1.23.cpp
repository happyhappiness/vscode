ESIElement::Pointer
esiSequence::makeUsable(esiTreeParentPtr newParent, ESIVarState &newVarState) const
{
    debugs(86, 5, "esiSequence::makeUsable: Creating usable Sequence");
    assert (processedcount == 0);
    assert (!failed);

    if (elements.size() == 0) {
        debugs(86, 5, "esiSequence::makeUsable: No elements in sequence " << this << ", returning NULL");
        return NULL;
    }

    esiSequence * resultS = new esiSequence (*this);
    ESIElement::Pointer result = resultS;
    resultS->parent = newParent;
    resultS->makeUsableElements(*this, newVarState);
    return result;
}
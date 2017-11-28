ESIElement::Pointer
esiSequence::makeCacheable() const
{
    debugs(86, 5, "esiSequence::makeCacheable: Making cachable sequence from " << this);
    assert (processedcount == 0);
    assert (!failed);

    if (elements.size() == 0) {
        debugs(86, 5, "esiSequence::makeCacheable: No elements in sequence " << this << ", returning NULL");
        return NULL;
    }

    esiSequence * resultS = new esiSequence (*this);
    ESIElement::Pointer result = resultS;
    resultS->makeCachableElements(*this);
    debugs(86, 5, "esiSequence::makeCacheable: " << this << " created " << result.getRaw());
    return result;
}
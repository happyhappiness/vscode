void
esiSequence::fail (ESIElement *source, char const *anError)
{
    failed = true;

    if (processing) {
        debugs(86, 5, "esiSequence::fail: " << this << " failure callback during processing");
        return;
    }

    debugs(86, 5, "esiSequence::fail: " << this << " has failed.");
    parent->fail (this, anError);
    elements.setNULL(0, elements.size());
    parent = NULL;
}
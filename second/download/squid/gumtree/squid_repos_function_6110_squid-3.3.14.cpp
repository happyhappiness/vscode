void
esiSequence::finish()
{
    debugs(86, 5, "esiSequence::finish: " << this << " is finished");
    elements.setNULL(0, elements.size());
    parent = NULL;
}
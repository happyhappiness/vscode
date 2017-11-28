void
ElementList::setNULL (int start, int end)
{
    assert (start >= 0 && start <= elementcount);
    assert (end >= 0 && end <= elementcount);

    for (int loopPosition = start; loopPosition < end; ++loopPosition) {
        if (elements[loopPosition].getRaw())
            elements[loopPosition]->finish();

        debugs(86, 5, "esiSequence::NULLElements: Setting index " <<
               loopPosition << ", pointer " <<
               elements[loopPosition].getRaw() << " to NULL");

        elements[loopPosition] = NULL;
    }
}
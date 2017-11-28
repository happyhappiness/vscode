void
ESISegment::dumpToLog() const
{
    ESISegment::Pointer temp = this;

    while (temp.getRaw()) {
        temp->dumpOne();
        temp = temp->next;
    }
}
void
ESISegmentFreeList (ESISegment::Pointer &head)
{
    while (head.getRaw()) {
        ESISegment::Pointer temp = head;
        head = head->next;
        temp->next = NULL;
    }
}
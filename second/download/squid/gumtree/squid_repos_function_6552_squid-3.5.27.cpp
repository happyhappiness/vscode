esiProcessResult_t
esiLiteral::process (int dovars)
{
    if (flags.donevars)
        return ESI_PROCESS_COMPLETE;

    if (dovars) {
        ESISegment::Pointer temp = buffer;
        /* Ensure variable state is clean */

        while (temp.getRaw()) {
            varState->feedData(temp->buf,temp->len);
            temp = temp->next;
        }

        /* free the pre-processed content */
        ESISegmentFreeList (buffer);

        buffer = varState->extractList ();
    }

    flags.donevars = 1;
    return ESI_PROCESS_COMPLETE;
}
void
esiSequence::render(ESISegment::Pointer output)
{
    /* append all processed elements, and trim processed
     * and rendered elements
     */
    assert (output->next == NULL);
    debugs (86,5, "esiSequenceRender: rendering " << processedcount << " elements");

    for (size_t i = 0; i < processedcount; ++i) {
        elements[i]->render(output);
        elements.setNULL(i,i+1);
        /* FIXME: pass a ESISegment ** ? */
        output = output->tail();
    }

    elements.pop_front (processedcount);
    processedcount = 0;
    assert (output->next == NULL);
}
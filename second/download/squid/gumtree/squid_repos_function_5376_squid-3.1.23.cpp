void
esiChoose::render(ESISegment::Pointer output)
{
    /* append all processed elements, and trim processed and rendered elements */
    assert (output->next == NULL);
    assert (elements.size() || otherwise.getRaw());
    debugs(86, 5, "esiChooseRender: rendering");

    if (chosenelement >= 0)
        elements[chosenelement]->render(output);
    else if (otherwise.getRaw())
        otherwise->render(output);
}
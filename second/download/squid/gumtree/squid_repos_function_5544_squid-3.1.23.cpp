void
ESIInclude::render(ESISegment::Pointer output)
{
    if (sent)
        return;

    ESISegment::Pointer myout;

    debugs(86, 5, "ESIIncludeRender: Rendering include " << this);

    assert (flags.finished || (flags.failed && flags.onerrorcontinue));

    if (flags.failed && flags.onerrorcontinue) {
        return;
    }

    /* Render the content */
    if (srccontent.getRaw()) {
        myout = srccontent;
        srccontent = NULL;
    } else if (altcontent.getRaw()) {
        myout = altcontent;
        altcontent = NULL;
    } else
        fatal ("ESIIncludeRender called with no content, and no failure!\n");

    assert (output->next == NULL);

    output->next = myout;

    sent = true;
}
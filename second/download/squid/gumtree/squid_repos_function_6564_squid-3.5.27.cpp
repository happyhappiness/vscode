void
esiTry::render(ESISegment::Pointer output)
{
    /* Try renders from it's children */
    assert (attempt.getRaw());
    assert (except.getRaw());
    debugs(86, 5, "esiTryRender: Rendering Try " << this);

    if (flags.attemptok) {
        attempt->render(output);
    } else if (flags.exceptok) {
        /* prerendered */

        if (exceptbuffer.getRaw())
            ESISegment::ListTransfer(exceptbuffer, output);
        else
            except->render(output);
    } else
        debugs(86, 5, "esiTryRender: Neither except nor attempt succeeded?!?");
}
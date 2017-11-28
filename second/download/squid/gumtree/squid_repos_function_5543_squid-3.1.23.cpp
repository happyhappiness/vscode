void
ESIInclude::start()
{
    /* prevent freeing ourselves */
    ESIIncludePtr foo(this);

    if (started)
        return;

    started = true;

    if (src.getRaw()) {
        Start (src, srcurl, varState);
        Start (alt, alturl, varState);
    } else {
        alt = NULL;

        debugs(86, 1, "ESIIncludeNew: esi:include with no src attributes");

        flags.failed = 1;
    }
}
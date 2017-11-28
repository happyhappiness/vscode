void
httpHdrScTargetDestroy(HttpHdrScTarget * sc)
{
    assert(sc);
    sc->target.clean();
    sc->content.clean();
    delete sc;
}
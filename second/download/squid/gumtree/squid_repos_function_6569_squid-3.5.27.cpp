void
esiTry::fail(ESIElement *source, char const *anError)
{
    assert (source);
    assert (source == attempt || source == except);
    debugs(86, 5, "esiTry::fail: this=" << this << ", source=" << source << ", message=" << anError);

    if (source == except) {
        flags.exceptfailed = 1;
    } else {
        flags.attemptfailed = 1;
    }

    notifyParent();
}
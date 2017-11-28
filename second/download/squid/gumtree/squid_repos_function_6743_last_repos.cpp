ESIElement::Pointer
esiTry::makeCacheable() const
{
    debugs(86, 5, "esiTry::makeCacheable: making cachable Try from " << this);
    esiTry *resultT = new esiTry (*this);
    ESIElement::Pointer result = resultT;

    if (attempt.getRaw())
        resultT->attempt = attempt->makeCacheable();

    if (except.getRaw())
        resultT->except  = except->makeCacheable();

    return result;
}
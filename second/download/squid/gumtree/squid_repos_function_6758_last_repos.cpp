ESIElement::Pointer
esiChoose::makeCacheable() const
{
    esiChoose *resultC = new esiChoose (*this);
    ESIElement::Pointer result = resultC;
    resultC->makeCachableElements(*this);

    if (otherwise.getRaw())
        resultC->otherwise = otherwise->makeCacheable();

    return result;
}
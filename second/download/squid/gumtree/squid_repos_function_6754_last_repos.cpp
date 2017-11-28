void
esiChoose::fail(ESIElement * source, char const *anError)
{
    checkValidSource (source);
    elements.setNULL (0, elements.size());

    if (otherwise.getRaw())
        otherwise->finish();

    otherwise = NULL;

    parent->fail(this, anError);

    parent = NULL;
}
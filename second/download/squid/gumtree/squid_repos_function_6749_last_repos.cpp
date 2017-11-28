void
esiChoose::finish()
{
    elements.setNULL(0, elements.size());

    if (otherwise.getRaw())
        otherwise->finish();

    otherwise = NULL;

    parent = NULL;
}
ESIAssign::Pointer
ESIAssign::makeCacheable() const
{
    ESIAssign *result = new ESIAssign (*this);

    if (variable.getRaw())
        result->variable = variable->makeCacheable();

    return result;
}
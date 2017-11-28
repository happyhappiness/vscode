void
ESIAssign::provideData (ESISegment::Pointer data, ESIElement * source)
{
    assert (source == variable.getRaw());
    char *result = data->listToChar();
    unevaluatedVariable = result;
    safe_free (result);
}
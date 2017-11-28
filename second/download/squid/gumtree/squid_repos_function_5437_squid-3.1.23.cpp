void
ESIAssign::finish()
{
    if (varState)
        cbdataReferenceDone (varState);

    if (parent.getRaw())
        parent = NULL;
}
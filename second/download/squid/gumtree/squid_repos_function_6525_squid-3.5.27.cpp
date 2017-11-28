void
ESIContext::finishChildren()
{
    if (tree.getRaw())
        tree->finish();

    tree = NULL;
}
void
LoadableModule::load(int mode)
{
    if (loaded())
        throw TexcHere("internal error: reusing LoadableModule object");

    theHandle = openModule(mode);

    if (!loaded())
        throw TexcHere(errorMsg());
}
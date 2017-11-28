void LoadableModule::unload()
{
    if (!loaded())
        throw TexcHere("internal error: unloading not loaded module");

    if (!closeModule())
        throw TexcHere(errorMsg());

    theHandle = 0;
}
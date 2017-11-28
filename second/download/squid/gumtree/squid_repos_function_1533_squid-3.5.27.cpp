static void
LoadModule(const char *fname)
{
    debugs(1, DBG_IMPORTANT, "Loading Squid module from '" << fname << "'");

    LoadableModule *m = new LoadableModule(fname);
    m->load();
    debugs(1, 2, "Loaded Squid module from '" << fname << "'");

    //TODO: TheModules.push_back(m);
}
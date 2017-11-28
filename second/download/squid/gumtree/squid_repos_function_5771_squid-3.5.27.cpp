void
Auth::Scheme::FreeAll()
{
    assert(shutting_down);

    while (GetSchemes().size()) {
        Auth::Scheme::Pointer scheme = GetSchemes().back();
        GetSchemes().pop_back();
        scheme->shutdownCleanup();
    }
}
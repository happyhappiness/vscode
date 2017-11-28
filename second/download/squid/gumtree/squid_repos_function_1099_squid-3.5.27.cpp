static void
free_HeaderManglers(HeaderManglers **pm)
{
    // we delete the entire http_header_* mangler configuration at once
    if (const HeaderManglers *manglers = *pm) {
        delete manglers;
        *pm = NULL;
    }
}
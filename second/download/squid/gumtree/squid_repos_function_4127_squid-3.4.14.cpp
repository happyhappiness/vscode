void Adaptation::Icap::ModXactLauncher::updateHistory(bool doStart)
{
    HttpRequest *r = virgin.cause ?
                     virgin.cause : dynamic_cast<HttpRequest*>(virgin.header);

    // r should never be NULL but we play safe; TODO: add Should()
    if (r) {
        Adaptation::Icap::History::Pointer h = r->icapHistory();
        if (h != NULL) {
            if (doStart)
                h->start("ICAPModXactLauncher");
            else
                h->stop("ICAPModXactLauncher");
        }
    }
}
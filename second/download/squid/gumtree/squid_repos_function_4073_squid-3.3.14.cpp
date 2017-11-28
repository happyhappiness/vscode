void Adaptation::Icap::ModXact::decideOnPreview()
{
    if (!TheConfig.preview_enable) {
        debugs(93, 5, HERE << "preview disabled by squid.conf");
        return;
    }

    const String urlPath = virginRequest().urlpath;
    size_t wantedSize;
    if (!service().wantsPreview(urlPath, wantedSize)) {
        debugs(93, 5, HERE << "should not offer preview for " << urlPath);
        return;
    }

    // we decided to do preview, now compute its size

    // cannot preview more than we can backup
    size_t ad = min(wantedSize, TheBackupLimit);

    if (!virginBody.expected())
        ad = 0;
    else if (virginBody.knownSize())
        ad = min(static_cast<uint64_t>(ad), virginBody.size()); // not more than we have

    debugs(93, 5, HERE << "should offer " << ad << "-byte preview " <<
           "(service wanted " << wantedSize << ")");

    preview.enable(ad);
    Must(preview.enabled());
}
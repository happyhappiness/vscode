void
Security::PeerConnector::startCertDownloading(SBuf &url)
{
    AsyncCall::Pointer certCallback = asyncCall(81, 4,
                                      "Security::PeerConnector::certDownloadingDone",
                                      PeerConnectorCertDownloaderDialer(&Security::PeerConnector::certDownloadingDone, this));

    const Downloader *csd = (request ? dynamic_cast<const Downloader*>(request->downloader.valid()) : nullptr);
    Downloader *dl = new Downloader(url, certCallback, XactionInitiator::initCertFetcher, csd ? csd->nestedLevel() + 1 : 1);
    AsyncJob::Start(dl);
}
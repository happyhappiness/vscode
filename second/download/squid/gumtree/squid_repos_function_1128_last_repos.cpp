void
Downloader::swanSong()
{
    debugs(33, 6, this);
    if (context_) {
        context_->finished();
        context_ = nullptr;
    }
}
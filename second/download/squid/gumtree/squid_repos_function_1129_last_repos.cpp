bool
Downloader::doneAll() const
{
    return (!callback_ || callback_->canceled()) && AsyncJob::doneAll();
}
void
HttpRequest::adaptHistoryImport(const HttpRequest &them)
{
    if (!adaptHistory_) {
        adaptHistory_ = them.adaptHistory_; // may be nil
    } else {
        // check that histories did not diverge
        Must(!them.adaptHistory_ || them.adaptHistory_ == adaptHistory_);
    }
}
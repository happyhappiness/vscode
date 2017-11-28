void
Downloader::callBack(Http::StatusCode const statusCode)
{
    CbDialer *dialer = dynamic_cast<CbDialer*>(callback_->getDialer());
    Must(dialer);
    dialer->status = statusCode;
    if (statusCode == Http::scOkay)
        dialer->object = object_;
    ScheduleCallHere(callback_);
    callback_ = nullptr;

    // We cannot deleteThis() because we may be called synchronously from
    // doCallouts() via handleReply() (XXX), and doCallouts() may crash if we
    // disappear. Instead, schedule an async call now so that later, when the
    // call firing code discovers a done() job, it deletes us.
    CallJobHere(33, 7, CbcPointer<Downloader>(this), Downloader, downloadFinished);
}
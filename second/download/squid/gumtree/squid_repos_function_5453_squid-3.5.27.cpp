void
Ftp::Client::ctrlClosed(const CommCloseCbParams &io)
{
    debugs(9, 4, status());
    ctrl.clear();
    doneWithFwd = "ctrlClosed()"; // assume FwdState is monitoring too
    mustStop("Ftp::Client::ctrlClosed");
}
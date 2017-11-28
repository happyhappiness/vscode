void
Ftp::Client::ctrlClosed(const CommCloseCbParams &)
{
    debugs(9, 4, status());
    ctrl.clear();
    doneWithFwd = "ctrlClosed()"; // assume FwdState is monitoring too
    mustStop("Ftp::Client::ctrlClosed");
}
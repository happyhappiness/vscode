void
FtpStateData::ctrlClosed(const CommCloseCbParams &io)
{
    debugs(9, 4, HERE);
    ctrl.clear();
    mustStop("FtpStateData::ctrlClosed");
}
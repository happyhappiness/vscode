void
FtpStateData::ctrlClosed(const CommCloseCbParams &io)
{
    ctrl.clear();
    deleteThis("FtpStateData::ctrlClosed");
}
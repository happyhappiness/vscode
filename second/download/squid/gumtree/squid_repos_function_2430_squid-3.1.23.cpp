static void
fwdServerFree(FwdServer * fs)
{
    cbdataReferenceDone(fs->_peer);
    memFree(fs, MEM_FWD_SERVER);
}
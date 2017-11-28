bool
CommConnectCbParams::syncWithComm()
{
    // drop the call if the call was scheduled before comm_close but
    // is being fired after comm_close
    if (fd >= 0 && fd_table[fd].closing()) {
        debugs(5, 3, HERE << "dropping late connect call: FD " << fd);
        return false;
    }
    return true; // now we are in sync and can handle the call
}
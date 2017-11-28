bool
CommIoCbParams::syncWithComm()
{
    // change parameters if the call was scheduled before comm_close but
    // is being fired after comm_close
    if (fd >= 0 && fd_table[fd].closing() && flag != COMM_ERR_CLOSING) {
        debugs(5, 3, HERE << "converting late call to COMM_ERR_CLOSING: FD " << fd);
        flag = COMM_ERR_CLOSING;
        size = 0;
    }
    return true; // now we are in sync and can handle the call
}
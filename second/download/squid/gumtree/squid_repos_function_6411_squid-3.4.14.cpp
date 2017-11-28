void Ipc::UdsSender::wrote(const CommIoCbParams& params)
{
    debugs(54, 5, HERE << params.conn << " flag " << params.flag << " retries " << retries << " [" << this << ']');
    writing = false;
    if (params.flag != COMM_OK && retries-- > 0) {
        // perhaps a fresh connection and more time will help?
        conn()->close();
        startSleep();
    }
}
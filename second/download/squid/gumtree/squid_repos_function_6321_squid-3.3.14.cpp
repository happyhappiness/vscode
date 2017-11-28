void Ipc::UdsSender::swanSong()
{
    // did we abort while waiting between retries?
    if (sleeping)
        cancelSleep();

    UdsOp::swanSong();
}
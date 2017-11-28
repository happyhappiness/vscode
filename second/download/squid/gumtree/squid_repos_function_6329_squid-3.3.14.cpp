void Ipc::UdsSender::delayedRetry()
{
    debugs(54, 5, HERE << sleeping);
    if (sleeping) {
        sleeping = false;
        write(); // reopens the connection if needed
    }
}
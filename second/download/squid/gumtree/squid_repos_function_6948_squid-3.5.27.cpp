void Ipc::UdsSender::timedout()
{
    debugs(54, 5, HERE);
    mustStop("timedout");
}
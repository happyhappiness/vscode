void Ipc::UdsSender::cancelSleep()
{
    if (sleeping) {
        // Why not delete the event? See Comm::ConnOpener::cancelSleep().
        sleeping = false;
        debugs(54, 9, "stops sleeping");
    }
}
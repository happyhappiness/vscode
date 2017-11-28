void
Log::TcpLogger::swanSong()
{
    disconnect(); // optional: refcounting should close/delete conn eventually
    AsyncJob::swanSong();
}
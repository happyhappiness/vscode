inline bool LoopDone(int i)
{
    return !Ping::Config.enable || (Ping::Config.count && i >= Ping::Config.count);
}
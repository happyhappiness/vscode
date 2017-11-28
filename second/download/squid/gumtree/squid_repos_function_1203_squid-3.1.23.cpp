void
Mem::Report()
{
    debugs(13, 3, "Memory pools are '" <<
           (Config.onoff.mem_pools ? "on" : "off")  << "'; limit: " <<
           std::setprecision(3) << toMB(MemPools::GetInstance().idleLimit()) <<
           " MB");
}
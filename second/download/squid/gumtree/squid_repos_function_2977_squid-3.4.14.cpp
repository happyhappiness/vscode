void
ClientDbRr::run(const RunnerRegistry &r)
{
    clientdbInit();
    Mgr::RegisterAction("client_list", "Cache Client List", clientdbDump, 0, 1);
}
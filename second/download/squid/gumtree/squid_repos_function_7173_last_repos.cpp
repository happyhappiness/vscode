String
Ipc::Port::CoordinatorAddr()
{
    static String coordinatorAddr;
    if (!coordinatorAddr.size()) {
        coordinatorAddr= channelPathPfx;
        coordinatorAddr.append(service_name.c_str());
        coordinatorAddr.append(coordinatorAddrLabel);
        coordinatorAddr.append(".ipc");
    }
    return coordinatorAddr;
}
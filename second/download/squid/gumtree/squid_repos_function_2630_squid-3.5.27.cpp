void
BroadcastSignalIfAny(int& sig)
{
    if (sig > 0) {
        if (IamCoordinatorProcess())
            Ipc::Coordinator::Instance()->broadcastSignal(sig);
        sig = -1;
    }
}
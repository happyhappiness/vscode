void
BroadcastSignalIfAny(int& sig)
{
    if (sig > 0) {
        if (IamMasterProcess()) {
            for (int i = TheKids.count() - 1; i >= 0; --i) {
                Kid& kid = TheKids.get(i);
                kill(kid.getPid(), sig);
            }
        }
        sig = -1;
    }
}
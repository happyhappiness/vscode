void Ipc::Coordinator::broadcastSignal(int sig) const
{
    typedef StrandCoords::const_iterator SCI;
    for (SCI iter = strands_.begin(); iter != strands_.end(); ++iter) {
        debugs(54, 5, HERE << "signal " << sig << " to kid" << iter->kidId <<
               ", PID=" << iter->pid);
        kill(iter->pid, sig);
    }
}
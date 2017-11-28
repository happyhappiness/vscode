bool
Ipc::Mem::Segment::Enabled()
{
    return !UsingSmp() && IamWorkerProcess();
}
void Ipc::UdsOp::noteTimeout(const CommTimeoutCbParams &)
{
    timedout(); // our kid handles communication timeout
}
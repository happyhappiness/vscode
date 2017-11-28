static inline bool
masterSignaled()
{
    return (DebugSignal > 0 || RotateSignal > 0 || ReconfigureSignal > 0 || ShutdownSignal > 0);
}
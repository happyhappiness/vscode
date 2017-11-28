void
IpcIoFile::scheduleTimeoutCheck()
{
    // we check all older requests at once so some may be wait for 2*Timeout
    eventAdd("IpcIoFile::CheckTimeouts", &IpcIoFile::CheckTimeouts,
             reinterpret_cast<void *>(diskId), Timeout, 0, false);
    timeoutCheckScheduled = true;
}
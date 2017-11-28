bool
ScheduleCall(const char *fileName, int fileLine, AsyncCall::Pointer &call)
{
    debugs(call->debugSection, call->debugLevel, fileName << "(" << fileLine <<
           ") will call " << *call << " [" << call->id << ']' );
    AsyncCallQueue::Instance().schedule(call);
    return true;
}
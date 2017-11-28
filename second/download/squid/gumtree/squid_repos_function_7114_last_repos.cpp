void Ipc::SendMessage(const String& toAddress, const TypedMsgHdr &message)
{
    AsyncJob::Start(new UdsSender(toAddress, message));
}
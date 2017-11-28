void
FtpStateData::writeReplyBody(const char *dataToWrite, size_t dataLength)
{
    debugs(9, 5, HERE << "writing " << dataLength << " bytes to the reply");
    addVirginReplyBody(dataToWrite, dataLength);
}
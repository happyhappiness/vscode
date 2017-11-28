void
FtpChannel::clear()
{
    fd = -1;
    closer = NULL;
}
void
request_flags::setResetTCP()
{
    debugs(73, 9, "request_flags::setResetTCP");
    reset_tcp = 1;
}
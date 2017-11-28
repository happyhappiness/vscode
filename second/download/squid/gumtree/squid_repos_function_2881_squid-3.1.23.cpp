void
request_flags::clearResetTCP()
{
    debugs(73, 9, "request_flags::clearResetTCP");
    reset_tcp = 0;
}
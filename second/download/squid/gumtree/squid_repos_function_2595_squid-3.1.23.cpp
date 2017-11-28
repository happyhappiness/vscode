void
FtpStateData::doneSendingRequestBody()
{
    debugs(9,3, HERE);
    dataComplete();
    /* NP: RFC 959  3.3.  DATA CONNECTION MANAGEMENT
     * if transfer type is 'stream' call dataComplete()
     * otherwise leave open. (reschedule control channel read?)
     */
}
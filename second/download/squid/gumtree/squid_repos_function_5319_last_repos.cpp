void
Ftp::Client::dataComplete()
{
    debugs(9, 3,status());

    /* Connection closed; transfer done. */

    /// Close data channel, if any, to conserve resources while we wait.
    data.close();

    /* expect the "transfer complete" message on the control socket */
    /*
     * DPW 2007-04-23
     * Previously, this was the only place where we set the
     * 'buffered_ok' flag when calling scheduleReadControlReply().
     * It caused some problems if the FTP server returns an unexpected
     * status code after the data command.  FtpStateData was being
     * deleted in the middle of dataRead().
     */
    /* AYJ: 2011-01-13: Bug 2581.
     * 226 status is possibly waiting in the ctrl buffer.
     * The connection will hang if we DONT send buffered_ok.
     * This happens on all transfers which can be completly sent by the
     * server before the 150 started status message is read in by Squid.
     * ie all transfers of about one packet hang.
     */
    scheduleReadControlReply(1);
}
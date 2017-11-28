void
FtpStateData::dataComplete()
{
    debugs(9, 3,HERE);

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
    scheduleReadControlReply(0);
}
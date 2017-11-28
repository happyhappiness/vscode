void
Ftp::Gateway::dataClosed(const CommCloseCbParams &io)
{
    Ftp::Client::dataClosed(io);
    failed(ERR_FTP_FAILURE, 0);
    /* failed closes ctrl.conn and frees ftpState */

    /* NP: failure recovery may be possible when its only a data.conn failure.
     *     if the ctrl.conn is still fine, we can send ABOR down it and retry.
     *     Just need to watch out for wider Squid states like shutting down or reconfigure.
     */
}
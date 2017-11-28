void
FtpStateData::dataClosed(const CommCloseCbParams &io)
{
    data.clear();
    failed(ERR_FTP_FAILURE, 0);
    /* failed closes ctrl.fd and frees ftpState */

    /* NP: failure recovery may be possible when its only a data.fd failure.
     *     is the ctrl.fd is still fine, we can send ABOR down it and retry.
     *     Just need to watch out for wider Squid states like shutting down or reconfigure.
     */
}
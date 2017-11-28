void
FtpStateData::dataClosed(const CommCloseCbParams &io)
{
    debugs(9, 4, HERE);
    if (data.listenConn != NULL) {
        data.listenConn->close();
        data.listenConn = NULL;
        // NP clear() does the: data.fd = -1;
    }
    data.clear();
    failed(ERR_FTP_FAILURE, 0);
    /* failed closes ctrl.conn and frees ftpState */

    /* NP: failure recovery may be possible when its only a data.conn failure.
     *     if the ctrl.conn is still fine, we can send ABOR down it and retry.
     *     Just need to watch out for wider Squid states like shutting down or reconfigure.
     */
}
 };
 
 /// handler called by Comm when FTP control channel is closed unexpectedly
 void
 FtpStateData::ctrlClosed(const CommCloseCbParams &io)
 {
+    debugs(9, 4, HERE);
     ctrl.clear();
-    deleteThis("FtpStateData::ctrlClosed");
+    mustStop("FtpStateData::ctrlClosed");
 }
 
 /// handler called by Comm when FTP data channel is closed unexpectedly
 void
 FtpStateData::dataClosed(const CommCloseCbParams &io)
 {
+    debugs(9, 4, HERE);
+    if (data.listenConn != NULL) {
+        data.listenConn->close();
+        data.listenConn = NULL;
+        // NP clear() does the: data.fd = -1;
+    }
     data.clear();
     failed(ERR_FTP_FAILURE, 0);
-    /* failed closes ctrl.fd and frees ftpState */
+    /* failed closes ctrl.conn and frees ftpState */
 
-    /* NP: failure recovery may be possible when its only a data.fd failure.
-     *     is the ctrl.fd is still fine, we can send ABOR down it and retry.
+    /* NP: failure recovery may be possible when its only a data.conn failure.
+     *     if the ctrl.conn is still fine, we can send ABOR down it and retry.
      *     Just need to watch out for wider Squid states like shutting down or reconfigure.
      */
 }
 
-FtpStateData::FtpStateData(FwdState *theFwdState) : AsyncJob("FtpStateData"), ServerStateData(theFwdState)
+FtpStateData::FtpStateData(FwdState *theFwdState, const Comm::ConnectionPointer &conn) : AsyncJob("FtpStateData"), ServerStateData(theFwdState)
 {
     const char *url = entry->url();
     debugs(9, 3, HERE << "'" << url << "'" );
-    statCounter.server.all.requests++;
-    statCounter.server.ftp.requests++;
+    ++ statCounter.server.all.requests;
+    ++ statCounter.server.ftp.requests;
     theSize = -1;
     mdtm = -1;
 
-    if (Config.Ftp.passive && !theFwdState->ftpPasvFailed())
+    if (Config.Ftp.passive && !flags.pasv_failed)
         flags.pasv_supported = 1;
 
     flags.rest_supported = 1;
 
     typedef CommCbMemFunT<FtpStateData, CommCloseCbParams> Dialer;
-    AsyncCall::Pointer closer = JobCallback(9, 5,
-                                            Dialer, this, FtpStateData::ctrlClosed);
-    ctrl.opened(theFwdState->server_fd, closer);
+    AsyncCall::Pointer closer = JobCallback(9, 5, Dialer, this, FtpStateData::ctrlClosed);
+    ctrl.opened(conn, closer);
 
     if (request->method == METHOD_PUT)
         flags.put = 1;
 }
 
 FtpStateData::~FtpStateData()

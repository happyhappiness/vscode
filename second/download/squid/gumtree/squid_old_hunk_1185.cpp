    /// Writes the data-transfer status reply to the FTP client and
    /// closes the data connection.
    void completeDataDownload();

    void calcUri(const SBuf *file);
    void changeState(const Ftp::ServerState newState, const char *reason);
    ClientSocketContext *handleUserRequest(const SBuf &cmd, SBuf &params);
    bool checkDataConnPost() const;
    void replyDataWritingCheckpoint();
    void maybeReadUploadData();

    void setReply(const int code, const char *msg);
    void writeCustomReply(const int code, const char *msg, const HttpReply *reply = NULL);

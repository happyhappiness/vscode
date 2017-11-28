void setPinnedConnection(ConnStateData *conn) {
        pinned_connection = cbdataReference(conn);
    }
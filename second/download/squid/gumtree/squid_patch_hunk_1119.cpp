         Comm::SetSelect(icpOutgoingConn->fd, COMM_SELECT_READ, icpHandleUdp, NULL, 0);
         fd_note(icpOutgoingConn->fd, "Outgoing ICP socket");
     }
 }
 
 static void
-icpIncomingConnectionOpened(const Comm::ConnectionPointer &conn, int errNo)
+icpIncomingConnectionOpened(const Comm::ConnectionPointer &conn, int)
 {
     if (!Comm::IsConnOpen(conn))
         fatal("Cannot open ICP Port");
 
     Comm::SetSelect(conn->fd, COMM_SELECT_READ, icpHandleUdp, NULL, 0);
 

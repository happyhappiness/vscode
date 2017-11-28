             SetSelect(conn->fd, COMM_SELECT_READ, doAccept, this, 0);
             return;
         }
 
         // A non-recoverable error; notify the caller */
         debugs(5, 5, HERE << "non-recoverable error:" << status() << " handler Subscription: " << theCallSub);
+        if (intendedForUserConnections())
+            logAcceptError(newConnDetails);
         notify(flag, newConnDetails);
         mustStop("Listener socket closed");
         return;
     }
 
     debugs(5, 5, HERE << "Listener: " << conn <<

         }
         SetSelect(fd, COMM_SELECT_READ, Comm::TcpAcceptor::doAccept, afd, 0);
 
     } catch (const std::exception &e) {
         fatalf("FATAL: error while accepting new client connection: %s\n", e.what());
     } catch (...) {
-        fatal("FATAL: error while accepting new client connection: [unkown]\n");
+        fatal("FATAL: error while accepting new client connection: [unknown]\n");
     }
 }
 
 bool
 Comm::TcpAcceptor::okToAccept()
 {

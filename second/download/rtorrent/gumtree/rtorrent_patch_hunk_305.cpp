 #include "manager.h"
 #include "poll_manager_epoll.h"
 #include "poll_manager_kqueue.h"
 #include "poll_manager_select.h"
 #include "view.h"
 
-namespace core {
-
-void
-receive_tracker_dump(const std::string& url, const char* data, size_t size) {
-  const std::string& filename = rpc::call_command_string("log.tracker");
-
-  if (filename.empty())
-    return;
+namespace std { using namespace tr1; }
 
-  std::fstream fstr(filename.c_str(), std::ios::out | std::ios::app);
-
-  if (!fstr.is_open())
-    return;
-
-  fstr << "url: " << url << std::endl << "---" << std::endl;
-  fstr.write(data, size);
-  fstr << std::endl <<"---" << std::endl;
-}
+namespace core {
 
 void
 Manager::handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash) {
   if (!rpc::call_command_value("log.handshake"))
     return;
   

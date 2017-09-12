@@ -40,7 +40,6 @@
 #endif
 
 #include <cstring>
-#include <cstdlib>
 #include <cassert>
 
 #include <sys/errno.h>
@@ -236,32 +235,15 @@ namespace
     return rtrim(line, CRLF);
   }
 
-  unsigned long unsigned_number_from_string(const string & data)
+  template <typename T>
+  T value_from_string(const string & data)
   {
-    errno = 0;
+    T value;
 
-    unsigned long value = strtoul(data.c_str(), NULL, 10);
-
-    if (value == ULONG_MAX && errno == ERANGE)
-      throw redis::value_error("invalid number; out of range of long");
-
-    if (value == 0 && errno == EINVAL)
-      throw redis::value_error("invalid number; unrecognized format");
-
-    return value;
-  }
-
-  redis::client::int_type number_from_string(const string & data)
-  {
-    errno = 0;
-
-    redis::client::int_type value = strtol(data.c_str(), NULL, 10);
-
-    if ((value == LONG_MAX || value == LONG_MIN) && errno == ERANGE)
-      throw redis::value_error("invalid number; out of range of long");
-
-    if (value == 0 && errno == EINVAL)
-      throw redis::value_error("invalid number; unrecognized format");
+    istringstream iss(data);
+    iss >> value;
+    if (iss.fail()) 
+      throw redis::value_error("invalid number");
 
     return value;
   }
@@ -284,6 +266,10 @@ namespace
   const string server_info_key_total_commands_processed = "total_commands_processed";
   const string server_info_key_uptime_in_seconds = "uptime_in_seconds";
   const string server_info_key_uptime_in_days = "uptime_in_days";
+  const string server_info_key_role = "role";
+
+  const string server_info_value_role_master = "master";
+  const string server_info_value_role_slave = "slave";
 }
 
 namespace redis 
@@ -578,11 +564,11 @@ namespace redis
     return recv_multi_bulk_reply_(out);
   }
 
-  void client::sinterstore(const client::string_type & dstkey, 
-                           const client::string_vector & keys)
+  client::int_type client::sinterstore(const client::string_type & dstkey, 
+                                       const client::string_vector & keys)
   {
     send_(makecmd("SINTERSTORE") << dstkey << ' ' << keys);
-    recv_ok_reply_();
+    return recv_int_reply_();
   }
 
   client::int_type client::sunion(const client::string_vector & keys,
@@ -592,11 +578,11 @@ namespace redis
     return recv_multi_bulk_reply_(out);
   }
 
-  void client::sunionstore(const client::string_type & dstkey, 
-                           const client::string_vector & keys)
+  client::int_type client::sunionstore(const client::string_type & dstkey, 
+                                       const client::string_vector & keys)
   {
     send_(makecmd("SUNIONSTORE") << dstkey << ' ' << keys);
-    recv_ok_reply_();
+    return recv_int_reply_();
   }
 
   client::int_type client::smembers(const client::string_type & key, 
@@ -746,25 +732,27 @@ namespace redis
       if (key == server_info_key_version)
         out.version = val;
       else if (key == server_info_key_bgsave_in_progress)
-        out.bgsave_in_progress = unsigned_number_from_string(val) == 1;
+        out.bgsave_in_progress = value_from_string<unsigned long>(val) == 1;
       else if (key == server_info_key_connected_clients)
-        out.connected_clients = unsigned_number_from_string(val);
+        out.connected_clients = value_from_string<unsigned long>(val);
       else if (key == server_info_key_connected_slaves)
-        out.connected_slaves = unsigned_number_from_string(val);
+        out.connected_slaves = value_from_string<unsigned long>(val);
       else if (key == server_info_key_used_memory)
-        out.used_memory = unsigned_number_from_string(val);
+        out.used_memory = value_from_string<unsigned long>(val);
       else if (key == server_info_key_changes_since_last_save)
-        out.changes_since_last_save = unsigned_number_from_string(val);
+        out.changes_since_last_save = value_from_string<unsigned long>(val);
       else if (key == server_info_key_last_save_time)
-        out.last_save_time = unsigned_number_from_string(val);
+        out.last_save_time = value_from_string<unsigned long>(val);
       else if (key == server_info_key_total_connections_received)
-        out.total_connections_received = unsigned_number_from_string(val);
+        out.total_connections_received = value_from_string<unsigned long>(val);
       else if (key == server_info_key_total_commands_processed)
-        out.total_commands_processed = unsigned_number_from_string(val);
+        out.total_commands_processed = value_from_string<unsigned long>(val);
       else if (key == server_info_key_uptime_in_seconds)
-        out.uptime_in_seconds = unsigned_number_from_string(val);
+        out.uptime_in_seconds = value_from_string<unsigned long>(val);
       else if (key == server_info_key_uptime_in_days)
-        out.uptime_in_days = unsigned_number_from_string(val);
+        out.uptime_in_days = value_from_string<unsigned long>(val);
+      else if (key == server_info_key_role)
+        out.role = val == server_info_value_role_master ? role_master : role_slave;
       else
         throw protocol_error(string("unexpected info key '") + key + "'");
     }
@@ -826,7 +814,7 @@ namespace redis
     if (line[0] != prefix)
       throw protocol_error("unexpected prefix for bulk reply");
 
-    return number_from_string(line.substr(1));
+    return value_from_string<client::int_type>(line.substr(1));
   }
 
   string client::recv_bulk_reply_() 
@@ -895,7 +883,7 @@ namespace redis
     if (line[0] != prefix_int_reply)
       throw protocol_error("unexpected prefix for integer reply");
 
-    return number_from_string(line.substr(1));
+    return value_from_string<client::int_type>(line.substr(1));
   }
 
   void client::recv_int_ok_reply_()
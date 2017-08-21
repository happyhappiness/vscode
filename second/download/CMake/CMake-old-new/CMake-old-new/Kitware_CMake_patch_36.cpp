@@ -355,8 +355,7 @@ static CURLcode file_upload(struct connectdata *conn)
       failf(data, "Can't get the size of %s", file->path);
       return CURLE_WRITE_ERROR;
     }
-    else
-      data->state.resume_from = (curl_off_t)file_stat.st_size;
+    data->state.resume_from = (curl_off_t)file_stat.st_size;
   }
 
   while(!result) {
@@ -476,7 +475,7 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
     time_t filetime;
     struct tm buffer;
     const struct tm *tm = &buffer;
-    snprintf(buf, sizeof(data->state.buffer),
+    snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),
              "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);
     result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
     if(result)
@@ -519,8 +518,7 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
       failf(data, "Can't get the size of file.");
       return CURLE_READ_ERROR;
     }
-    else
-      data->state.resume_from += (curl_off_t)statbuf.st_size;
+    data->state.resume_from += (curl_off_t)statbuf.st_size;
   }
 
   if(data->state.resume_from <= expected_size)
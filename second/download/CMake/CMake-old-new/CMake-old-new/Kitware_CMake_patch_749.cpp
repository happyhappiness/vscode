@@ -50,7 +50,7 @@ ::Load(const char* name)
     buf = new char[n + 2 + 1];
     sprintf(buf, "%s/*", name);
     }
-  struct _finddata_t data;	// data of current file
+  struct _finddata_t data;      // data of current file
   
   // Now put them into the file array
   size_t srchHandle = _findfirst(buf, &data);
@@ -109,13 +109,13 @@ ::Load(const char* name)
  */
 const char* 
 cmDirectory
-::GetFile(size_t index)
+::GetFile(size_t dindex)
 {
-  if ( index >= m_Files.size() )
+  if ( dindex >= m_Files.size() )
     {
     cmSystemTools::Error("Bad index for GetFile on cmDirectory\n", 0);
     return 0;
     }
-  return m_Files[index].c_str();
+  return m_Files[dindex].c_str();
 }
 
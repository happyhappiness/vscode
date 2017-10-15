   if (!((CurlGet*)handle)->stream()->write((const char*)data, size * nmemb).fail())
     return size * nmemb;
   else
     return 0;
 }
 
-CurlGet::CurlGet(CurlStack* s) :
-  m_handle(NULL),
-  m_stack(s) {
-
-  if (m_stack == NULL)
-    throw std::logic_error("Tried to create CurlGet without a valid CurlStack");
-}
-
 CurlGet::~CurlGet() {
   close();
 }
 
-CurlGet*
-CurlGet::new_object(CurlStack* s) {
-  return new CurlGet(s);
-}
-
 void
 CurlGet::start() {
   if (is_busy())
-    throw std::logic_error("Tried to call CurlGet::start on a busy object");
+    throw torrent::internal_error("Tried to call CurlGet::start on a busy object.");
 
   if (m_stream == NULL)
-    throw std::logic_error("Tried to call CurlGet::start without a valid output stream");
+    throw torrent::internal_error("Tried to call CurlGet::start without a valid output stream.");
 
   m_handle = curl_easy_init();
 
   curl_easy_setopt(m_handle, CURLOPT_URL,            m_url.c_str());
   curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION,  &curl_get_receive_write);
   curl_easy_setopt(m_handle, CURLOPT_WRITEDATA,      this);

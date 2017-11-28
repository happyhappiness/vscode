 
     xfree(name);
     return m;
 }
 
 MimeIcon::MimeIcon(const char *aName) :
-    icon_(xstrdup(aName))
+    url_(nullptr)
 {
-    url_ = xstrdup(internalLocalUri("/squid-internal-static/icons/", icon_));
+    setName(aName);
 }
 
 MimeIcon::~MimeIcon()
 {
-    xfree(icon_);
     xfree(url_);
 }
 
 void
 MimeIcon::setName(char const *aString)
 {
-    xfree(icon_);
     xfree(url_);
-    icon_ = xstrdup(aString);
+    icon_ = aString;
     url_ = xstrdup(internalLocalUri("/squid-internal-static/icons/", icon_));
 }
 
-char const *
+SBuf
 MimeIcon::getName() const
 {
     return icon_;
 }
 
-char const *
+const SBuf
 mimeGetIcon(const char *fn)
 {
     MimeEntry *m = mimeGetEntry(fn, 1);
 
-    if (m == NULL)
-        return NULL;
-
-    if (!strcmp(m->theIcon.getName(), dash_str))
-        return NULL;
+    if (!m || !m->theIcon.getName().cmp(dash_str))
+        return SBuf();
 
     return m->theIcon.getName();
 }
 
 const char *
 mimeGetIconURL(const char *fn)
 {
-    char const *icon = mimeGetIcon(fn);
+    SBuf icon(mimeGetIcon(fn));
 
-    if (icon == NULL)
+    if (icon.isEmpty())
         return null_string;
 
     if (Config.icons.use_short_names) {
-        static MemBuf mb;
-        mb.reset();
-        mb.Printf("/squid-internal-static/icons/%s", icon);
-        return mb.content();
+        static SBuf mb;
+        mb.clear();
+        mb.append("/squid-internal-static/icons/");
+        mb.append(icon);
+        return mb.c_str();
     } else {
         return internalLocalUri("/squid-internal-static/icons/", icon);
     }
 }
 
 const char *

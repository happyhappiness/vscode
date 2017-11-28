         else
             safe_free(p->date);
     }
 
 found:
 
-    for (i = 0; i < n_tokens; i++)
+    for (i = 0; i < n_tokens; ++i)
         xfree(tokens[i]);
 
     if (!p->name)
         ftpListPartsFree(&p);	/* cleanup */
 
     return p;
 }
 
-/// \ingroup ServerProtocolFTPInternal
-static const char *
-dots_fill(size_t len)
-{
-    static char buf[256];
-    size_t i = 0;
-
-    if (len > Config.Ftp.list_width) {
-        memset(buf, ' ', 256);
-        buf[0] = '\n';
-        buf[Config.Ftp.list_width + 4] = '\0';
-        return buf;
-    }
-
-    for (i = len; i < Config.Ftp.list_width; i++)
-        buf[i - len] = (i % 2) ? '.' : ' ';
-
-    buf[i - len] = '\0';
-
-    return buf;
-}
-
-char *
+MemBuf *
 FtpStateData::htmlifyListEntry(const char *line)
 {
-    LOCAL_ARRAY(char, icon, 2048);
-    LOCAL_ARRAY(char, href, 2048 + 40);
-    LOCAL_ARRAY(char, text, 2048);
-    LOCAL_ARRAY(char, size, 2048);
-    LOCAL_ARRAY(char, chdir, 2048 + 40);
-    LOCAL_ARRAY(char, view, 2048 + 40);
-    LOCAL_ARRAY(char, download, 2048 + 40);
-    LOCAL_ARRAY(char, link, 2048 + 40);
-    LOCAL_ARRAY(char, html, 8192);
-    LOCAL_ARRAY(char, prefix, 2048);
-    size_t width = Config.Ftp.list_width;
+    char icon[2048];
+    char href[2048 + 40];
+    char text[ 2048];
+    char size[ 2048];
+    char chdir[ 2048 + 40];
+    char view[ 2048 + 40];
+    char download[ 2048 + 40];
+    char link[ 2048 + 40];
+    MemBuf *html;
+    char prefix[2048];
     ftpListParts *parts;
-    *icon = *href = *text = *size = *chdir = *view = *download = *link = *html = '\0';
+    *icon = *href = *text = *size = *chdir = *view = *download = *link = '\0';
 
-    if ((int) strlen(line) > 1024) {
-        snprintf(html, 8192, "%s\n", line);
+    debugs(9, 7, HERE << " line ={" << line << "}");
+
+    if (strlen(line) > 1024) {
+        html = new MemBuf();
+        html->init();
+        html->Printf("<tr><td colspan=\"5\">%s</td></tr>\n", line);
         return html;
     }
 
     if (flags.dir_slash && dirpath && typecode != 'D')
         snprintf(prefix, 2048, "%s/", rfc1738_escape_part(dirpath));
     else
         prefix[0] = '\0';
 
-    /* Handle builtin <dirup> */
-    if (strcmp(line, "<internal-dirup>") == 0) {
-        /* <A HREF="{href}">{icon}</A> <A HREF="{href}">{text}</A> {link} */
-        snprintf(icon, 2048, "<IMG border=\"0\" SRC=\"%s\" ALT=\"%-6s\">",
-                 mimeGetIconURL("internal-dirup"),
-                 "[DIRUP]");
-
-        if (!flags.no_dotdot && !flags.root_dir) {
-            /* Normal directory */
-
-            if (!flags.dir_slash)
-                strcpy(href, "../");
-            else
-                strcpy(href, "./");
-
-            strcpy(text, "Parent Directory");
-        } else if (!flags.no_dotdot && flags.root_dir) {
-            /* "Top level" directory */
-            strcpy(href, "%2e%2e/");
-            strcpy(text, "Parent Directory");
-            snprintf(link, 2048, "(<A HREF=\"%s\">%s</A>)",
-                     "%2f/",
-                     "Root Directory");
-        } else if (flags.no_dotdot && !flags.root_dir) {
-            char *url;
-            /* Normal directory where last component is / or ..  */
-            strcpy(href, "%2e%2e/");
-            strcpy(text, "Parent Directory");
-
-            if (flags.dir_slash) {
-                url = xstrdup("./");
-            } else {
-                const char *title = title_url.termedBuf();
-                int k = 6 + strcspn(&title[6], "/");
-                char *t;
-                url = xstrdup(title + k);
-                t = url + strlen(url) - 2;
-
-                while (t > url && *t != '/')
-                    *t-- = '\0';
-            }
-
-            snprintf(link, 2048, "(<A HREF=\"%s\">%s</A>)", url, "Back");
-            safe_free(url);
-        } else {		/* NO_DOTDOT && ROOT_DIR */
-            /* "UNIX Root" directory */
-            strcpy(href, "/");
-            strcpy(text, "Home Directory");
-        }
-
-        snprintf(html, 8192, "<A HREF=\"%s\">%s</A> <A HREF=\"%s\">%s</A> %s\n",
-                 href, icon, href, text, link);
-        return html;
-    }
-
     if ((parts = ftpListParseParts(line, flags)) == NULL) {
         const char *p;
-        snprintf(html, 8192, "%s\n", line);
 
-        for (p = line; *p && xisspace(*p); p++);
+        html = new MemBuf();
+        html->init();
+        html->Printf("<tr class=\"entry\"><td colspan=\"5\">%s</td></tr>\n", line);
+
+        for (p = line; *p && xisspace(*p); ++p);
         if (*p && !xisspace(*p))
             flags.listformat_unknown = 1;
 
         return html;
     }
 
     if (!strcmp(parts->name, ".") || !strcmp(parts->name, "..")) {
-        *html = '\0';
         ftpListPartsFree(&parts);
-        return html;
+        return NULL;
     }
 
     parts->size += 1023;
     parts->size >>= 10;
     parts->showname = xstrdup(parts->name);
 
-    if (!Config.Ftp.list_wrap) {
-        if (strlen(parts->showname) > width - 1) {
-            *(parts->showname + width - 1) = '>';
-            *(parts->showname + width - 0) = '\0';
-        }
-    }
-
     /* {icon} {text} . . . {date}{size}{chdir}{view}{download}{link}\n  */
     xstrncpy(href, rfc1738_escape_part(parts->name), 2048);
 
     xstrncpy(text, parts->showname, 2048);
 
     switch (parts->type) {
 
     case 'd':
-        snprintf(icon, 2048, "<IMG border=\"0\" SRC=\"%s\" ALT=\"%-6s\">",
+        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                  mimeGetIconURL("internal-dir"),
                  "[DIR]");
         strcat(href, "/");	/* margin is allocated above */
         break;
 
     case 'l':
-        snprintf(icon, 2048, "<IMG border=\"0\" SRC=\"%s\" ALT=\"%-6s\">",
+        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                  mimeGetIconURL("internal-link"),
                  "[LINK]");
         /* sometimes there is an 'l' flag, but no "->" link */
 
         if (parts->link) {
             char *link2 = xstrdup(html_quote(rfc1738_escape(parts->link)));
-            snprintf(link, 2048, " -> <A HREF=\"%s%s\">%s</A>",
+            snprintf(link, 2048, " -&gt; <a href=\"%s%s\">%s</a>",
                      *link2 != '/' ? prefix : "", link2,
                      html_quote(parts->link));
             safe_free(link2);
         }
 
         break;
 
     case '\0':
-        snprintf(icon, 2048, "<IMG border=\"0\" SRC=\"%s\" ALT=\"%-6s\">",
+        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                  mimeGetIconURL(parts->name),
                  "[UNKNOWN]");
-        snprintf(chdir, 2048, " <A HREF=\"%s/;type=d\"><IMG border=\"0\" SRC=\"%s\" "
-                 "ALT=\"[DIR]\"></A>",
+        snprintf(chdir, 2048, "<a href=\"%s/;type=d\"><img border=\"0\" src=\"%s\" "
+                 "alt=\"[DIR]\"></a>",
                  rfc1738_escape_part(parts->name),
                  mimeGetIconURL("internal-dir"));
         break;
 
     case '-':
 
     default:
-        snprintf(icon, 2048, "<IMG border=\"0\" SRC=\"%s\" ALT=\"%-6s\">",
+        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                  mimeGetIconURL(parts->name),
                  "[FILE]");
         snprintf(size, 2048, " %6" PRId64 "k", parts->size);
         break;
     }
 
     if (parts->type != 'd') {
         if (mimeGetViewOption(parts->name)) {
-            snprintf(view, 2048, " <A HREF=\"%s%s;type=a\"><IMG border=\"0\" SRC=\"%s\" "
-                     "ALT=\"[VIEW]\"></A>",
+            snprintf(view, 2048, "<a href=\"%s%s;type=a\"><img border=\"0\" src=\"%s\" "
+                     "alt=\"[VIEW]\"></a>",
                      prefix, href, mimeGetIconURL("internal-view"));
         }
 
         if (mimeGetDownloadOption(parts->name)) {
-            snprintf(download, 2048, " <A HREF=\"%s%s;type=i\"><IMG border=\"0\" SRC=\"%s\" "
-                     "ALT=\"[DOWNLOAD]\"></A>",
+            snprintf(download, 2048, "<a href=\"%s%s;type=i\"><img border=\"0\" src=\"%s\" "
+                     "alt=\"[DOWNLOAD]\"></a>",
                      prefix, href, mimeGetIconURL("internal-download"));
         }
     }
 
-    /* <A HREF="{href}">{icon}</A> <A HREF="{href}">{text}</A> . . . {date}{size}{chdir}{view}{download}{link}\n  */
-    if (parts->type != '\0') {
-        snprintf(html, 8192, "<A HREF=\"%s%s\">%s</A> <A HREF=\"%s%s\">%s</A>%s "
-                 "%s%8s%s%s%s%s\n",
-                 prefix, href, icon, prefix, href, html_quote(text), dots_fill(strlen(text)),
-                 parts->date, size, chdir, view, download, link);
-    } else {
-        /* Plain listing. {icon} {text} ... {chdir}{view}{download} */
-        snprintf(html, 8192, "<A HREF=\"%s%s\">%s</A> <A HREF=\"%s%s\">%s</A>%s "
-                 "%s%s%s%s\n",
-                 prefix, href, icon, prefix, href, html_quote(text), dots_fill(strlen(text)),
+    /* construct the table row from parts. */
+    html = new MemBuf();
+    html->init();
+    html->Printf("<tr class=\"entry\">"
+                 "<td class=\"icon\"><a href=\"%s%s\">%s</a></td>"
+                 "<td class=\"filename\"><a href=\"%s%s\">%s</a></td>"
+                 "<td class=\"date\">%s</td>"
+                 "<td class=\"size\">%s</td>"
+                 "<td class=\"actions\">%s%s%s%s</td>"
+                 "</tr>\n",
+                 prefix, href, icon,
+                 prefix, href, html_quote(text),
+                 parts->date,
+                 size,
                  chdir, view, download, link);
-    }
 
     ftpListPartsFree(&parts);
     return html;
 }
 
 void

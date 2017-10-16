 #include <string.h>
 /* The last #include file should be: */
 #ifdef MALLOCDEBUG
 #include "memdebug.h"
 #endif
 
-/* infof() is for info message along the way */
+/* returns last node in linked list */
+static struct curl_slist *slist_get_last(struct curl_slist *list)
+{
+	struct curl_slist	*item;
+
+	/* if caller passed us a NULL, return now */
+	if (!list)
+		return NULL;
+
+	/* loop through to find the last item */
+	item = list;
+	while (item->next) {
+		item = item->next;
+	}
+	return item;
+}
+
+/* append a struct to the linked list. It always retunrs the address of the
+ * first record, so that you can sure this function as an initialization
+ * function as well as an append function. If you find this bothersome,
+ * then simply create a separate _init function and call it appropriately from
+ * within the proram. */
+struct curl_slist *curl_slist_append(struct curl_slist *list,
+                                     const char *data)
+{
+	struct curl_slist	*last;
+	struct curl_slist	*new_item;
+
+	new_item = (struct curl_slist *) malloc(sizeof(struct curl_slist));
+	if (new_item) {
+		new_item->next = NULL;
+		new_item->data = strdup(data);
+	}
+	else {
+		fprintf(stderr, "Cannot allocate memory for QUOTE list.\n");
+		return NULL;
+	}
+
+	if (list) {
+		last = slist_get_last(list);
+		last->next = new_item;
+		return list;
+	}
+
+	/* if this is the first item, then new_item *is* the list */
+	return new_item;
+}
+
+/* be nice and clean up resources */
+void curl_slist_free_all(struct curl_slist *list)
+{
+	struct curl_slist	*next;
+	struct curl_slist	*item;
+
+	if (!list)
+		return;
+
+	item = list;
+	do {
+		next = item->next;
+		
+		if (item->data) {
+			free(item->data);
+		}
+		free(item);
+		item = next;
+	} while (next);
+}
+
+
+/* Curl_infof() is for info message along the way */
 
 void Curl_infof(struct UrlData *data, char *fmt, ...)
 {
   va_list ap;
   if(data->bits.verbose) {
     va_start(ap, fmt);
     fputs("* ", data->err);
     vfprintf(data->err, fmt, ap);
     va_end(ap);
   }
 }
 
-/* failf() is for messages stating why we failed, the LAST one will be
+/* Curl_failf() is for messages stating why we failed, the LAST one will be
    returned for the user (if requested) */
 
 void Curl_failf(struct UrlData *data, char *fmt, ...)
 {
   va_list ap;
   va_start(ap, fmt);
   if(data->errorbuffer)
     vsnprintf(data->errorbuffer, CURL_ERROR_SIZE, fmt, ap);
-  else /* no errorbuffer receives this, write to data->err instead */
+  else if(!data->bits.mute) {
+    /* no errorbuffer receives this, write to data->err instead */
     vfprintf(data->err, fmt, ap);
+    fprintf(data->err, "\n");
+  }
   va_end(ap);
 }
 
 /* Curl_sendf() sends formated data to the server */
 size_t Curl_sendf(int sockfd, struct connectdata *conn,
                   char *fmt, ...)

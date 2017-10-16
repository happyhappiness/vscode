   bar->width = scr_size[0] - 1;
 #endif
 
   bar->out = config->errors;
 }
 
+static
+void dump(const char *text,
+          FILE *stream, unsigned char *ptr, size_t size,
+          bool nohex)
+{
+  size_t i;
+  size_t c;
+
+  unsigned int width=0x10;
+
+  if(nohex)
+    /* without the hex output, we can fit more on screen */
+    width = 0x40;
+
+  fprintf(stream, "%s, %d bytes (0x%x)\n", text, size, size);
+
+  for(i=0; i<size; i+= width) {
+
+    fprintf(stream, "%04x: ", i);
+
+    if(!nohex) {
+      /* hex not disabled, show it */
+      for(c = 0; c < width; c++)
+        if(i+c < size)
+          fprintf(stream, "%02x ", ptr[i+c]);
+        else
+          fputs("   ", stream);
+    }
+
+    for(c = 0; (c < width) && (i+c < size); c++) {
+      /* check for 0D0A; if found, skip past and start a new line of output */
+      if (nohex && (i+c+1 < size) && ptr[i+c]==0x0D && ptr[i+c+1]==0x0A) {
+        i+=(c+2-width);
+        break;
+      }
+      fprintf(stream, "%c",
+              (ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.');
+      /* check again for 0D0A, to avoid an extra \n if it's at width */
+      if (nohex && (i+c+2 < size) && ptr[i+c+1]==0x0D && ptr[i+c+2]==0x0A) {
+        i+=(c+3-width);
+        break;
+      }
+    }
+    fputc('\n', stream); /* newline */
+  }
+}
+
+static
+int my_trace(CURL *handle, curl_infotype type,
+             unsigned char *data, size_t size,
+             void *userp)
+{
+  struct Configurable *config = (struct Configurable *)userp;
+  FILE *output=config->errors;
+  const char *text;
+
+  (void)handle; /* prevent compiler warning */
+
+  if(!config->trace_stream) {
+    /* open for append */
+    if(strequal("-", config->trace_dump))
+      config->trace_stream = stdout;
+    else {
+      config->trace_stream = fopen(config->trace_dump, "w");
+      config->trace_fopened = TRUE;
+    }
+  }
+
+  if(config->trace_stream)
+    output = config->trace_stream;
+
+  switch (type) {
+  case CURLINFO_TEXT:
+    fprintf(output, "== Info: %s", data);
+  default: /* in case a new one is introduced to shock us */
+    return 0;
+
+  case CURLINFO_HEADER_OUT:
+    text = "=> Send header";
+    break;
+  case CURLINFO_DATA_OUT:
+    text = "=> Send data ";
+    break;
+  case CURLINFO_HEADER_IN:
+    text = "<= Recv header";
+    break;
+  case CURLINFO_DATA_IN:
+    text = "<= Recv data";
+    break;
+  }
+
+  dump(text, output, data, size, config->trace_ascii);
+  return 0;
+}
+
 void free_config_fields(struct Configurable *config)
 {
   if(config->random_file)
     free(config->random_file);
   if(config->egd_file)
     free(config->egd_file);

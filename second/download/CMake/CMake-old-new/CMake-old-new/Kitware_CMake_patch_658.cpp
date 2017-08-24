@@ -1,16 +1,16 @@
 /***************************************************************************
- *                                  _   _ ____  _     
- *  Project                     ___| | | |  _ \| |    
- *                             / __| | | | |_) | |    
- *                            | (__| |_| |  _ <| |___ 
+ *                                  _   _ ____  _
+ *  Project                     ___| | | |  _ \| |
+ *                             / __| | | | |_) | |
+ *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
  * are also available at http://curl.haxx.se/docs/copyright.html.
- * 
+ *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
  * furnished to do so, under the terms of the COPYING file.
@@ -97,313 +97,53 @@ Content-Type: text/plain
 Content-Disposition: form-data; name="FILECONTENT"
 ...
 
-  For the old FormParse used by curl_formparse use:
-
-  gcc -DHAVE_CONFIG_H -I../ -g -D_OLD_FORM_DEBUG -o formdata -I../include formdata.c strequal.c
-
-  run the 'formdata' executable and make sure the output is ok!
-
-  try './formdata "name=Daniel" "poo=noo" "foo=bar"' and similarly
-
  */
 
 #include "setup.h"
+#include <curl/curl.h>
+
+/* Length of the random boundary string. */
+#define BOUNDARY_LENGTH 40
 
 #ifndef CURL_DISABLE_HTTP
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdarg.h>
-
 #include <time.h>
-
-#include <curl/curl.h>
+#include <sys/stat.h>
 #include "formdata.h"
-
 #include "strequal.h"
+#include "memory.h"
+
+#define _MPRINTF_REPLACE /* use our functions only */
+#include <curl/mprintf.h>
 
 /* The last #include file should be: */
-#ifdef MALLOCDEBUG
 #include "memdebug.h"
-#endif
-
-/* Length of the random boundary string. The risk of this being used
-   in binary data is very close to zero, 64^32 makes
-   6277101735386680763835789423207666416102355444464034512896
-   combinations... */
-#define BOUNDARY_LENGTH 32
 
 /* What kind of Content-Type to use on un-specified files with unrecognized
    extensions. */
-#define HTTPPOST_CONTENTTYPE_DEFAULT "text/plain"
-
-/* This is a silly duplicate of the function in main.c to enable this source
-   to compile stand-alone for better debugging */
-static void GetStr(char **string,
-                   const char *value)
-{
-  if(*string)
-    free(*string);
-  *string = strdup(value);
-}
-
-/***************************************************************************
- *
- * FormParse()
- *      
- * Reads a 'name=value' paramter and builds the appropriate linked list.
- *
- * Specify files to upload with 'name=@filename'. Supports specified
- * given Content-Type of the files. Such as ';type=<content-type>'.
- *
- * You may specify more than one file for a single name (field). Specify
- * multiple files by writing it like:
- *
- * 'name=@filename,filename2,filename3'
- *
- * If you want content-types specified for each too, write them like:
- *
- * 'name=@filename;type=image/gif,filename2,filename3'
- *
- ***************************************************************************/
+#define HTTPPOST_CONTENTTYPE_DEFAULT "application/octet-stream"
 
 #define FORM_FILE_SEPARATOR ','
 #define FORM_TYPE_SEPARATOR ';'
 
-static
-int FormParse(char *input,
-              struct curl_httppost **httppost,
-              struct curl_httppost **last_post)
-{
-  /* nextarg MUST be a string in the format 'name=contents' and we'll
-     build a linked list with the info */
-  char name[256];
-  char *contents;
-  char major[128];
-  char minor[128];
-  long flags = 0;
-  char *contp;
-  const char *type = NULL;
-  char *prevtype = NULL;
-  char *sep;
-  char *sep2;
-  struct curl_httppost *post;
-  struct curl_httppost *subpost; /* a sub-node */
-  unsigned int i;
-
-  /* Preallocate contents to the length of input to make sure we don't
-     overwrite anything. */
-  contents = malloc(strlen(input));
-  contents[0] = '\000';
- 
-  if(1 <= sscanf(input, "%255[^=]=%[^\n]", name, contents)) {
-    /* the input was using the correct format */
-    contp = contents;
-
-    if('@' == contp[0]) {
-      /* we use the @-letter to indicate file name(s) */
-      
-      flags = HTTPPOST_FILENAME;
-      contp++;
-
-      post=NULL;
-
-      do {
-        /* since this was a file, it may have a content-type specifier
-           at the end too */
-
-        sep=strchr(contp, FORM_TYPE_SEPARATOR);
-        sep2=strchr(contp, FORM_FILE_SEPARATOR);
-
-        /* pick the closest */
-        if(sep2 && (sep2 < sep)) {
-          sep = sep2;
-
-          /* no type was specified! */
-        }
-        if(sep) {
-
-          /* if we got here on a comma, don't do much */
-          if(FORM_FILE_SEPARATOR != *sep)
-            type = strstr(sep+1, "type=");
-          else
-            type=NULL;
-
-          *sep=0; /* terminate file name at separator */
-
-          if(type) {
-            type += strlen("type=");
-            
-            if(2 != sscanf(type, "%127[^/]/%127[^,\n]",
-                           major, minor)) {
-              free(contents);
-              return 2; /* illegal content-type syntax! */
-            }
-            /* now point beyond the content-type specifier */
-            sep = (char *)type + strlen(major)+strlen(minor)+1;
-
-            /* find the following comma */
-            sep=strchr(sep, FORM_FILE_SEPARATOR);
-          }
-        }
-        else {
-          type=NULL;
-          sep=strchr(contp, FORM_FILE_SEPARATOR);
-        }
-        if(sep) {
-          /* the next file name starts here */
-          *sep =0;
-          sep++;
-        }
-        if(!type) {
-          /*
-           * No type was specified, we scan through a few well-known
-           * extensions and pick the first we match!
-           */
-          struct ContentType {
-            const char *extension;
-            const char *type;
-          };
-          static struct ContentType ctts[]={
-            {".gif",  "image/gif"},
-            {".jpg",  "image/jpeg"},
-            {".jpeg", "image/jpeg"},
-            {".txt",  "text/plain"},
-            {".html", "text/plain"}
-          };
-
-          if(prevtype)
-            /* default to the previously set/used! */
-            type = prevtype;
-          else
-            /* It seems RFC1867 defines no Content-Type to default to
-               text/plain so we don't actually need to set this: */
-            type = HTTPPOST_CONTENTTYPE_DEFAULT;
-
-          for(i=0; i<sizeof(ctts)/sizeof(ctts[0]); i++) {
-            if(strlen(contp) >= strlen(ctts[i].extension)) {
-              if(strequal(contp +
-                          strlen(contp) - strlen(ctts[i].extension),
-                          ctts[i].extension)) {
-                type = ctts[i].type;
-                break;
-              }       
-            }
-          }
-          /* we have a type by now */
-        }
-
-        if(NULL == post) {
-          /* For the first file name, we allocate and initiate the main list
-             node */
-
-          post = (struct curl_httppost *)malloc(sizeof(struct curl_httppost));
-          if(post) {
-            memset(post, 0, sizeof(struct curl_httppost));
-            GetStr(&post->name, name);      /* get the name */
-            GetStr(&post->contents, contp); /* get the contents */
-            post->contentslength = 0;
-            post->flags = flags;
-            if(type) {
-              GetStr(&post->contenttype, (char *)type); /* get type */
-              prevtype=post->contenttype; /* point to the allocated string! */
-            }
-            /* make the previous point to this */
-            if(*last_post)
-              (*last_post)->next = post;
-            else
-              (*httppost) = post;
-
-            (*last_post) = post;          
-          }
-
-        }
-        else {
-          /* we add a file name to the previously allocated node, known as
-             'post' now */
-          subpost =(struct curl_httppost *)
-            malloc(sizeof(struct curl_httppost));
-          if(subpost) {
-             memset(subpost, 0, sizeof(struct curl_httppost));
-             GetStr(&subpost->name, name);      /* get the name */
-             GetStr(&subpost->contents, contp); /* get the contents */
-             subpost->contentslength = 0;
-             subpost->flags = flags;
-             if(type) {
-               GetStr(&subpost->contenttype, (char *)type); /* get type */
-               prevtype=subpost->contenttype; /* point to allocated string! */
-             }
-             /* now, point our 'more' to the original 'more' */
-             subpost->more = post->more;
-
-             /* then move the original 'more' to point to ourselves */
-             post->more = subpost;           
-          }
-        }
-        contp = sep; /* move the contents pointer to after the separator */
-      } while(sep && *sep); /* loop if there's another file name */
-    }
-    else {
-      post = (struct curl_httppost *)malloc(sizeof(struct curl_httppost));
-      if(post) {
-        memset(post, 0, sizeof(struct curl_httppost));
-        GetStr(&post->name, name);      /* get the name */
-        if( contp[0]=='<' ) {
-          GetStr(&post->contents, contp+1); /* get the contents */
-          post->contentslength = 0;
-          post->flags = HTTPPOST_READFILE;
-        }
-        else {
-          GetStr(&post->contents, contp); /* get the contents */
-          post->contentslength = 0;
-          post->flags = 0;
-        }
-
-        /* make the previous point to this */
-        if(*last_post)
-          (*last_post)->next = post;
-        else
-          (*httppost) = post;
-
-        (*last_post) = post;      
-      }
-
-    }
-
-  }
-  else {
-    free(contents);
-    return 1;
-  }
-  free(contents);
-  return 0;
-}
-
-int curl_formparse(char *input,
-                   struct curl_httppost **httppost,
-                   struct curl_httppost **last_post)
-{
-  return FormParse(input, httppost, last_post);
-}
-
 /***************************************************************************
  *
  * AddHttpPost()
- *      
+ *
  * Adds a HttpPost structure to the list, if parent_post is given becomes
  * a subpost of parent_post instead of a direct list element.
  *
  * Returns newly allocated HttpPost on success and NULL if malloc failed.
  *
  ***************************************************************************/
 static struct curl_httppost *
-AddHttpPost(char * name, long namelength,
-            char * value, long contentslength,
-
-            /* CMC: Added support for buffer uploads */
-            char * buffer, long bufferlength,
-
+AddHttpPost(char * name, size_t namelength,
+            char * value, size_t contentslength,
+            char * buffer, size_t bufferlength,
             char *contenttype,
             long flags,
             struct curl_slist* contentHeader,
@@ -413,49 +153,45 @@ AddHttpPost(char * name, long namelength,
             struct curl_httppost **last_post)
 {
   struct curl_httppost *post;
-  post = (struct curl_httppost *)malloc(sizeof(struct curl_httppost));
+  post = (struct curl_httppost *)calloc(sizeof(struct curl_httppost), 1);
   if(post) {
-    memset(post, 0, sizeof(struct curl_httppost));
     post->name = name;
-    post->namelength = name?(namelength?namelength:(long)strlen(name)):0;
+    post->namelength = (long)(name?(namelength?namelength:strlen(name)):0);
     post->contents = value;
-    post->contentslength = contentslength;
-
-    /* CMC: Added support for buffer uploads */
+    post->contentslength = (long)contentslength;
     post->buffer = buffer;
-    post->bufferlength = bufferlength;
-
+    post->bufferlength = (long)bufferlength;
     post->contenttype = contenttype;
     post->contentheader = contentHeader;
     post->showfilename = showfilename;
     post->flags = flags;
   }
   else
     return NULL;
-  
+
   if (parent_post) {
     /* now, point our 'more' to the original 'more' */
     post->more = parent_post->more;
-    
+
     /* then move the original 'more' to point to ourselves */
-    parent_post->more = post;            
+    parent_post->more = post;
   }
   else {
     /* make the previous point to this */
     if(*last_post)
       (*last_post)->next = post;
     else
       (*httppost) = post;
-    
-    (*last_post) = post;  
+
+    (*last_post) = post;
   }
   return post;
 }
 
 /***************************************************************************
  *
  * AddFormInfo()
- *      
+ *
  * Adds a FormInfo structure to the list presented by parent_form_info.
  *
  * Returns newly allocated FormInfo on success and NULL if malloc failed/
@@ -478,11 +214,11 @@ static FormInfo * AddFormInfo(char *value,
   }
   else
     return NULL;
-  
+
   if (parent_form_info) {
     /* now, point our 'more' to the original 'more' */
     form_info->more = parent_form_info->more;
-    
+
     /* then move the original 'more' to point to ourselves */
     parent_form_info->more = form_info;
   }
@@ -495,7 +231,7 @@ static FormInfo * AddFormInfo(char *value,
 /***************************************************************************
  *
  * ContentTypeForFilename()
- *      
+ *
  * Provides content type for filename if one of the known types (else
  * (either the prevtype or the default is returned).
  *
@@ -520,25 +256,25 @@ static const char * ContentTypeForFilename (const char *filename,
     {".jpg",  "image/jpeg"},
     {".jpeg", "image/jpeg"},
     {".txt",  "text/plain"},
-    {".html", "text/plain"}
+    {".html", "text/html"}
   };
-  
+
   if(prevtype)
     /* default to the previously set/used! */
     contenttype = prevtype;
   else
     /* It seems RFC1867 defines no Content-Type to default to
        text/plain so we don't actually need to set this: */
     contenttype = HTTPPOST_CONTENTTYPE_DEFAULT;
-  
+
   for(i=0; i<sizeof(ctts)/sizeof(ctts[0]); i++) {
     if(strlen(filename) >= strlen(ctts[i].extension)) {
       if(strequal(filename +
                   strlen(filename) - strlen(ctts[i].extension),
                   ctts[i].extension)) {
         contenttype = ctts[i].type;
         break;
-      }       
+      }
     }
   }
   /* we have a contenttype by now */
@@ -547,41 +283,45 @@ static const char * ContentTypeForFilename (const char *filename,
 
 /***************************************************************************
  *
- * AllocAndCopy()
- *      
- * Copies the data currently available under *buffer using newly allocated
- * buffer (that becomes *buffer). Uses buffer_length if not null, else
- * uses strlen to determine the length of the buffer to be copied
+ * memdup()
+ *
+ * Copies the 'source' data to a newly allocated buffer buffer (that is
+ * returned). Uses buffer_length if not null, else uses strlen to determine
+ * the length of the buffer to be copied
  *
- * Returns 0 on success and 1 if the malloc failed.
+ * Returns the new pointer or NULL on failure.
  *
  ***************************************************************************/
-static int AllocAndCopy (char **buffer, int buffer_length)
+static char *memdup(const char *src, size_t buffer_length)
 {
-  const char *src = *buffer;
-  int length, add = 0;
+  size_t length;
+  bool add = FALSE;
+  char *buffer;
+
   if (buffer_length)
     length = buffer_length;
   else {
-    length = (int)strlen(*buffer);
-    add = 1;
+    length = strlen(src);
+    add = TRUE;
   }
-  *buffer = (char*)malloc(length+add);
-  if (!*buffer)
-    return 1;
-  memcpy(*buffer, src, length);
+  buffer = (char*)malloc(length+add);
+  if (!buffer)
+    return NULL; /* fail */
+
+  memcpy(buffer, src, length);
+
   /* if length unknown do null termination */
   if (add)
-    (*buffer)[length] = '\0';
-  return 0;
+    buffer[length] = '\0';
+
+  return buffer;
 }
 
 /***************************************************************************
  *
  * FormAdd()
- *      
- * Stores a 'name=value' formpost parameter and builds the appropriate
- * linked list.
+ *
+ * Stores a formpost parameter and builds the appropriate linked list.
  *
  * Has two principal functionalities: using files and byte arrays as
  * post parts. Byte arrays are either copied or just the pointer is stored
@@ -631,7 +371,7 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
                      struct curl_httppost **last_post,
                      va_list params)
 {
-  FormInfo *first_form, *current_form, *form;
+  FormInfo *first_form, *current_form, *form = NULL;
   CURLFORMcode return_value = CURL_FORMADD_OK;
   const char *prevtype = NULL;
   struct curl_httppost *post = NULL;
@@ -647,22 +387,16 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
   /*
    * We need to allocate the first struct to fill in.
    */
-  first_form = (FormInfo *)malloc(sizeof(struct FormInfo));
-  if(first_form) {
-    memset(first_form, 0, sizeof(FormInfo));
-    current_form = first_form;
-  }
-  else
+  first_form = (FormInfo *)calloc(sizeof(struct FormInfo), 1);
+  if(!first_form)
     return CURL_FORMADD_MEMORY;
 
+  current_form = first_form;
+
   /*
-   * Loop through all the options set.
+   * Loop through all the options set. Break if we have an error to report.
    */
-  while (1) {
-
-    /* break if we have an error to report */
-    if (return_value != CURL_FORMADD_OK)
-      break;
+  while (return_value == CURL_FORMADD_OK) {
 
     /* first see if we have more parts of the array param */
     if ( array_state ) {
@@ -757,7 +491,12 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
           array_value:va_arg(params, char *);
         if (filename) {
           current_form->value = strdup(filename);
-          current_form->flags |= HTTPPOST_READFILE;
+          if(!current_form->value)
+            return_value = CURL_FORMADD_MEMORY;
+          else {
+            current_form->flags |= HTTPPOST_READFILE;
+            current_form->value_alloc = TRUE;
+          }
         }
         else
           return_value = CURL_FORMADD_NULL;
@@ -784,16 +523,21 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
             return_value = CURL_FORMADD_OPTION_TWICE;
         }
         else {
-          if (filename)
+          if (filename) {
             current_form->value = strdup(filename);
+            if(!current_form->value)
+              return_value = CURL_FORMADD_MEMORY;
+            else {
+              current_form->flags |= HTTPPOST_FILENAME;
+              current_form->value_alloc = TRUE;
+            }
+          }
           else
             return_value = CURL_FORMADD_NULL;
-          current_form->flags |= HTTPPOST_FILENAME;
         }
         break;
       }
 
-    /* CMC: Added support for buffer uploads */
     case CURLFORM_BUFFER:
       {
         char *filename = array_state?array_value:
@@ -813,16 +557,18 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
             return_value = CURL_FORMADD_OPTION_TWICE;
         }
         else {
-          if (filename)
+          if (filename) {
             current_form->value = strdup(filename);
+            if(!current_form->value)
+              return_value = CURL_FORMADD_MEMORY;
+          }
           else
             return_value = CURL_FORMADD_NULL;
           current_form->flags |= HTTPPOST_BUFFER;
         }
         break;
       }
-      
-    /* CMC: Added support for buffer uploads */
+
     case CURLFORM_BUFFERPTR:
         current_form->flags |= HTTPPOST_PTRBUFFER;
       if (current_form->buffer)
@@ -837,7 +583,6 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
       }
       break;
 
-    /* CMC: Added support for buffer uploads */
     case CURLFORM_BUFFERLENGTH:
       if (current_form->bufferlength)
         return_value = CURL_FORMADD_OPTION_TWICE;
@@ -865,8 +610,13 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
             return_value = CURL_FORMADD_OPTION_TWICE;
         }
         else {
-          if (contenttype)
+          if (contenttype) {
             current_form->contenttype = strdup(contenttype);
+            if(!current_form->contenttype)
+              return_value = CURL_FORMADD_MEMORY;
+            else
+              current_form->contenttype_alloc = TRUE;
+          }
           else
             return_value = CURL_FORMADD_NULL;
         }
@@ -876,20 +626,15 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
       {
         /* this "cast increases required alignment of target type" but
            we consider it OK anyway */
-        struct curl_slist* list=0;
-        if ( array_state )
-          {
-          memcpy(&list, &array_value, sizeof(struct curl_slist*));
-          }
-        else
-          {
-          list = va_arg(params, struct curl_slist*);
-          }
+        struct curl_slist* list = array_state?
+          (struct curl_slist*)array_value:
+          va_arg(params, struct curl_slist*);
+
         if( current_form->contentheader )
           return_value = CURL_FORMADD_OPTION_TWICE;
         else
           current_form->contentheader = list;
-        
+
         break;
       }
     case CURLFORM_FILENAME:
@@ -898,8 +643,13 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
           va_arg(params, char *);
         if( current_form->showfilename )
           return_value = CURL_FORMADD_OPTION_TWICE;
-        else
+        else {
           current_form->showfilename = strdup(filename);
+          if(!current_form->showfilename)
+            return_value = CURL_FORMADD_MEMORY;
+          else
+            current_form->showfilename_alloc = TRUE;
+        }
         break;
       }
     default:
@@ -910,7 +660,7 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
   if(CURL_FORMADD_OK == return_value) {
     /* go through the list, check for copleteness and if everything is
      * alright add the HttpPost item otherwise set return_value accordingly */
-    
+
     post = NULL;
     for(form = first_form;
         form != NULL;
@@ -921,7 +671,6 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
            ( (form->flags & HTTPPOST_FILENAME) &&
              (form->flags & HTTPPOST_PTRCONTENTS) ) ||
 
-           /* CMC: Added support for buffer uploads */
            ( (!form->buffer) &&
              (form->flags & HTTPPOST_BUFFER) &&
              (form->flags & HTTPPOST_PTRBUFFER) ) ||
@@ -939,53 +688,74 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
           /* our contenttype is missing */
           form->contenttype
             = strdup(ContentTypeForFilename(form->value, prevtype));
+          if(!form->contenttype) {
+            return_value = CURL_FORMADD_MEMORY;
+            break;
+          }
+          form->contenttype_alloc = TRUE;
         }
         if ( !(form->flags & HTTPPOST_PTRNAME) &&
              (form == first_form) ) {
           /* copy name (without strdup; possibly contains null characters) */
-          if (AllocAndCopy(&form->name, form->namelength)) {
+          form->name = memdup(form->name, form->namelength);
+          if (!form->name) {
             return_value = CURL_FORMADD_MEMORY;
             break;
           }
+          form->name_alloc = TRUE;
         }
         if ( !(form->flags & HTTPPOST_FILENAME) &&
-             !(form->flags & HTTPPOST_READFILE) && 
+             !(form->flags & HTTPPOST_READFILE) &&
              !(form->flags & HTTPPOST_PTRCONTENTS) &&
-
-             /* CMC: Added support for buffer uploads */
              !(form->flags & HTTPPOST_PTRBUFFER) ) {
-
           /* copy value (without strdup; possibly contains null characters) */
-          if (AllocAndCopy(&form->value, form->contentslength)) {
+          form->value = memdup(form->value, form->contentslength);
+          if (!form->value) {
             return_value = CURL_FORMADD_MEMORY;
             break;
           }
+          form->value_alloc = TRUE;
         }
         post = AddHttpPost(form->name, form->namelength,
                            form->value, form->contentslength,
-
-                           /* CMC: Added support for buffer uploads */
                            form->buffer, form->bufferlength,
-
                            form->contenttype, form->flags,
                            form->contentheader, form->showfilename,
                            post, httppost,
                            last_post);
-        
-        if(!post)
+
+        if(!post) {
           return_value = CURL_FORMADD_MEMORY;
+          break;
+        }
 
         if (form->contenttype)
           prevtype = form->contenttype;
       }
     }
   }
 
+  if(return_value) {
+    /* we return on error, free possibly allocated fields */
+    if(!form)
+      form = current_form;
+    if(form) {
+      if(form->name_alloc)
+        free(form->name);
+      if(form->value_alloc)
+        free(form->value);
+      if(form->contenttype_alloc)
+        free(form->contenttype);
+      if(form->showfilename_alloc)
+        free(form->showfilename);
+    }
+  }
+
   /* always delete the allocated memory before returning */
   form = first_form;
   while (form != NULL) {
     FormInfo *delete_form;
-    
+
     delete_form = form;
     form = form->more;
     free (delete_form);
@@ -994,9 +764,13 @@ CURLFORMcode FormAdd(struct curl_httppost **httppost,
   return return_value;
 }
 
+/*
+ * curl_formadd() is a public API to add a section to the multipart formpost.
+ */
+
 CURLFORMcode curl_formadd(struct curl_httppost **httppost,
-                 struct curl_httppost **last_post,
-                 ...)
+                          struct curl_httppost **last_post,
+                          ...)
 {
   va_list arg;
   CURLFORMcode result;
@@ -1006,88 +780,101 @@ CURLFORMcode curl_formadd(struct curl_httppost **httppost,
   return result;
 }
 
-static int AddFormData(struct FormData **formp,
-                       const void *line,
-                       long length)
+/*
+ * AddFormData() adds a chunk of data to the FormData linked list.
+ *
+ * size is incremented by the chunk length, unless it is NULL
+ */
+static CURLcode AddFormData(struct FormData **formp,
+                            enum formtype type,
+                            const void *line,
+                            size_t length,
+                            curl_off_t *size)
 {
   struct FormData *newform = (struct FormData *)
     malloc(sizeof(struct FormData));
+  if (!newform)
+    return CURLE_OUT_OF_MEMORY;
   newform->next = NULL;
 
   /* we make it easier for plain strings: */
   if(!length)
-    length = (long)strlen((char *)line);
+    length = strlen((char *)line);
 
   newform->line = (char *)malloc(length+1);
+  if (!newform->line) {
+    free(newform);
+    return CURLE_OUT_OF_MEMORY;
+  }
   memcpy(newform->line, line, length);
   newform->length = length;
   newform->line[length]=0; /* zero terminate for easier debugging */
-  
+  newform->type = type;
+
   if(*formp) {
     (*formp)->next = newform;
     *formp = newform;
   }
   else
     *formp = newform;
 
-  return length;
+  if (size) {
+    if(type == FORM_DATA)
+      *size += length;
+    else {
+      /* Since this is a file to be uploaded here, add the size of the actual
+         file */
+      if(!strequal("-", newform->line)) {
+        struct stat file;
+        if(!stat(newform->line, &file)) {
+          *size += file.st_size;
+        }
+      }
+    }
+  }
+  return CURLE_OK;
 }
 
+/*
+ * AddFormDataf() adds printf()-style formatted data to the formdata chain.
+ */
 
-static int AddFormDataf(struct FormData **formp,
-                        const char *fmt, ...)
+static CURLcode AddFormDataf(struct FormData **formp,
+                             curl_off_t *size,
+                             const char *fmt, ...)
 {
   char s[4096];
   va_list ap;
   va_start(ap, fmt);
-  vsprintf(s, fmt, ap);
+  vsnprintf(s, sizeof(s), fmt, ap);
   va_end(ap);
 
-  return AddFormData(formp, s, 0);
+  return AddFormData(formp, FORM_DATA, s, 0, size);
 }
 
-
-char *Curl_FormBoundary(void)
-{
-  char *retstring;
-  static int randomizer=0; /* this is just so that two boundaries within
-                              the same form won't be identical */
-  int i;
-
-  static char table62[]=
-    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
-
-  retstring = (char *)malloc(BOUNDARY_LENGTH);
-
-  if(!retstring)
-    return NULL; /* failed */
-
-  srand((unsigned int)(time(NULL)+randomizer++)); /* seed */
-
-  strcpy(retstring, "curl"); /* bonus commercials 8*) */
-
-  for(i=4; i<(BOUNDARY_LENGTH-1); i++) {
-    retstring[i] = table62[rand()%62];
-  }
-  retstring[BOUNDARY_LENGTH-1]=0; /* zero terminate */
-
-  return retstring;
-}
-
-/* Used from http.c, this cleans a built FormData linked list */ 
+/*
+ * Curl_formclean() is used from http.c, this cleans a built FormData linked
+ * list
+ */
 void Curl_formclean(struct FormData *form)
 {
   struct FormData *next;
 
+  if(!form)
+    return;
+
   do {
     next=form->next;  /* the following form line */
     free(form->line); /* free the line */
     free(form);       /* free the struct */
-  
+
   } while((form=next)); /* continue */
 }
 
-/* external function to free up a whole form post chain */
+/*
+ * curl_formfree() is an external function to free up a whole form post
+ * chain
+ */
 void curl_formfree(struct curl_httppost *form)
 {
   struct curl_httppost *next;
@@ -1116,16 +903,23 @@ void curl_formfree(struct curl_httppost *form)
   } while((form=next)); /* continue */
 }
 
+/*
+ * Curl_getFormData() converts a linked list of "meta data" into a complete
+ * (possibly huge) multipart formdata. The input list is in 'post', while the
+ * output resulting linked lists gets stored in '*finalform'. *sizep will get
+ * the total size of the whole POST.
+ */
+
 CURLcode Curl_getFormData(struct FormData **finalform,
                           struct curl_httppost *post,
-                          int *sizep)
+                          curl_off_t *sizep)
 {
   struct FormData *form = NULL;
   struct FormData *firstform;
   struct curl_httppost *file;
   CURLcode result = CURLE_OK;
 
-  int size =0;
+  curl_off_t size=0; /* support potentially ENORMOUS formposts */
   char *boundary;
   char *fileboundary=NULL;
   struct curl_slist* curList;
@@ -1136,41 +930,62 @@ CURLcode Curl_getFormData(struct FormData **finalform,
     return result; /* no input => no output! */
 
   boundary = Curl_FormBoundary();
-  
+  if(!boundary)
+    return CURLE_OUT_OF_MEMORY;
+
   /* Make the first line of the output */
-  AddFormDataf(&form,
-               "Content-Type: multipart/form-data;"
-               " boundary=%s\r\n",
-               boundary);
-  /* we DO NOT count that line since that'll be part of the header! */
+  result = AddFormDataf(&form, NULL,
+                        "Content-Type: multipart/form-data;"
+                        " boundary=%s\r\n",
+                        boundary);
+  if (result) {
+    free(boundary);
+    return result;
+  }
+  /* we DO NOT include that line in the total size of the POST, since it'll be
+     part of the header! */
 
   firstform = form;
-  
+
   do {
 
-    if(size)
-      size += AddFormDataf(&form, "\r\n");
+    if(size) {
+      result = AddFormDataf(&form, &size, "\r\n");
+      if (result)
+        break;
+    }
 
     /* boundary */
-    size += AddFormDataf(&form, "--%s\r\n", boundary);
+    result = AddFormDataf(&form, &size, "--%s\r\n", boundary);
+    if (result)
+      break;
 
-    size += AddFormData(&form,
-                        "Content-Disposition: form-data; name=\"", 0);
+    result = AddFormDataf(&form, &size,
+                          "Content-Disposition: form-data; name=\"");
+    if (result)
+      break;
 
-    size += AddFormData(&form, post->name, post->namelength);
+    result = AddFormData(&form, FORM_DATA, post->name, post->namelength,
+                         &size);
+    if (result)
+      break;
 
-    size += AddFormData(&form, "\"", 0);
+    result = AddFormDataf(&form, &size, "\"");
+    if (result)
+      break;
 
     if(post->more) {
       /* If used, this is a link to more file names, we must then do
          the magic to include several files with the same field name */
 
       fileboundary = Curl_FormBoundary();
 
-      size += AddFormDataf(&form,
-                           "\r\nContent-Type: multipart/mixed,"
-                           " boundary=%s\r\n",
-                           fileboundary);
+      result = AddFormDataf(&form, &size,
+                            "\r\nContent-Type: multipart/mixed,"
+                            " boundary=%s\r\n",
+                            fileboundary);
+      if (result)
+        break;
     }
 
     file = post;
@@ -1183,111 +998,167 @@ CURLcode Curl_getFormData(struct FormData **finalform,
 
       if(post->more) {
         /* if multiple-file */
-        size += AddFormDataf(&form,
-                             "\r\n--%s\r\nContent-Disposition: "
-                             "attachment; filename=\"%s\"",
-                             fileboundary,
-                             (file->showfilename?file->showfilename:
-                              file->contents));
+        result = AddFormDataf(&form, &size,
+                              "\r\n--%s\r\nContent-Disposition: "
+                              "attachment; filename=\"%s\"",
+                              fileboundary,
+                              (file->showfilename?file->showfilename:
+                               file->contents));
+        if (result)
+          break;
       }
       else if((post->flags & HTTPPOST_FILENAME) ||
-
-              /* CMC: Added support for buffer uploads */
               (post->flags & HTTPPOST_BUFFER)) {
 
-        size += AddFormDataf(&form,
-                             "; filename=\"%s\"",
-                             (post->showfilename?post->showfilename:
-                              post->contents));
+        result = AddFormDataf(&form, &size,
+                              "; filename=\"%s\"",
+                              (post->showfilename?post->showfilename:
+                               post->contents));
+        if (result)
+          break;
       }
-      
+
       if(file->contenttype) {
         /* we have a specified type */
-        size += AddFormDataf(&form,
-                             "\r\nContent-Type: %s",
-                             file->contenttype);
+        result = AddFormDataf(&form, &size,
+                              "\r\nContent-Type: %s",
+                              file->contenttype);
+        if (result)
+          break;
       }
 
       curList = file->contentheader;
       while( curList ) {
         /* Process the additional headers specified for this form */
-        size += AddFormDataf( &form, "\r\n%s", curList->data );
+        result = AddFormDataf( &form, &size, "\r\n%s", curList->data );
+        if (result)
+          break;
         curList = curList->next;
       }
+      if (result) {
+        Curl_formclean(firstform);
+        free(boundary);
+        return result;
+      }
 
 #if 0
       /* The header Content-Transfer-Encoding: seems to confuse some receivers
        * (like the built-in PHP engine). While I can't see any reason why it
        * should, I can just as well skip this to the benefit of the users who
        * are using such confused receivers.
        */
-      
+
       if(file->contenttype &&
          !checkprefix("text/", file->contenttype)) {
         /* this is not a text content, mention our binary encoding */
         size += AddFormData(&form, "\r\nContent-Transfer-Encoding: binary", 0);
       }
 #endif
 
-      size += AddFormData(&form, "\r\n\r\n", 0);
+      result = AddFormDataf(&form, &size, "\r\n\r\n");
+      if (result)
+        break;
 
       if((post->flags & HTTPPOST_FILENAME) ||
          (post->flags & HTTPPOST_READFILE)) {
         /* we should include the contents from the specified file */
         FILE *fileread;
-        char buffer[1024];
-        int nread;
-
-        fileread = strequal("-", file->contents)?stdin:
-          /* binary read for win32 crap */
-          /*VMS??*/ fopen(file->contents, "rb");  /* ONLY ALLOWS FOR STREAM FILES ON VMS */
-        /*VMS?? Stream files are OK, as are FIXED & VAR files WITHOUT implied CC */
-        /*VMS?? For implied CC, every record needs to have a \n appended & 1 added to SIZE */
-        if(fileread) {
-          while((nread = (int)fread(buffer, 1, 1024, fileread)))
-            size += AddFormData(&form, buffer, nread);
 
-          if(fileread != stdin)
+        fileread = strequal("-", file->contents)?
+          stdin:fopen(file->contents, "rb"); /* binary read for win32  */
+
+        /*
+         * VMS: This only allows for stream files on VMS.  Stream files are
+         * OK, as are FIXED & VAR files WITHOUT implied CC For implied CC,
+         * every record needs to have a \n appended & 1 added to SIZE
+         */
+
+        if(fileread) {
+          if(fileread != stdin) {
+            /* close the file again */
             fclose(fileread);
+            /* add the file name only - for later reading from this */
+            result = AddFormData(&form, FORM_FILE, file->contents, 0, &size);
+          }
+          else {
+            /* When uploading from stdin, we can't know the size of the file,
+             * thus must read the full file as before. We *could* use chunked
+             * transfer-encoding, but that only works for HTTP 1.1 and we
+             * can't be sure we work with such a server.
+             */
+            size_t nread;
+            char buffer[512];
+            while((nread = fread(buffer, 1, sizeof(buffer), fileread))) {
+              result = AddFormData(&form, FORM_DATA, buffer, nread, &size);
+              if (result)
+                break;
+            }
+          }
+
+          if (result) {
+            Curl_formclean(firstform);
+            free(boundary);
+            return result;
+          }
+
         }
         else {
-#if 0
-          /* File wasn't found, add a nothing field! */
-          size += AddFormData(&form, "", 0);
-#endif
           Curl_formclean(firstform);
           free(boundary);
           *finalform = NULL;
           return CURLE_READ_ERROR;
         }
 
-        /* CMC: Added support for buffer uploads */
-      } else if (post->flags & HTTPPOST_BUFFER) {
-          /* include contents of buffer */
-          size += AddFormData(&form, post->buffer, post->bufferlength);
+      }
+      else if (post->flags & HTTPPOST_BUFFER) {
+        /* include contents of buffer */
+        result = AddFormData(&form, FORM_DATA, post->buffer,
+                             post->bufferlength, &size);
+          if (result)
+            break;
       }
 
       else {
         /* include the contents we got */
-        size += AddFormData(&form, post->contents, post->contentslength);
+        result = AddFormData(&form, FORM_DATA, post->contents,
+                             post->contentslength, &size);
+        if (result)
+          break;
       }
     } while((file = file->more)); /* for each specified file for this field */
+    if (result) {
+      Curl_formclean(firstform);
+      free(boundary);
+      return result;
+    }
 
     if(post->more) {
       /* this was a multiple-file inclusion, make a termination file
          boundary: */
-      size += AddFormDataf(&form,
+      result = AddFormDataf(&form, &size,
                            "\r\n--%s--",
-                           fileboundary);     
+                           fileboundary);
       free(fileboundary);
+      if (result)
+        break;
     }
 
   } while((post=post->next)); /* for each field */
+  if (result) {
+    Curl_formclean(firstform);
+    free(boundary);
+    return result;
+  }
 
   /* end-boundary for everything */
-  size += AddFormDataf(&form,
+  result = AddFormDataf(&form, &size,
                        "\r\n--%s--\r\n",
                        boundary);
+  if (result) {
+    Curl_formclean(firstform);
+    free(boundary);
+    return result;
+  }
 
   *sizep = size;
 
@@ -1298,36 +1169,68 @@ CURLcode Curl_getFormData(struct FormData **finalform,
   return result;
 }
 
+/*
+ * Curl_FormInit() inits the struct 'form' points to with the 'formdata'
+ * and resets the 'sent' counter.
+ */
 int Curl_FormInit(struct Form *form, struct FormData *formdata )
 {
   if(!formdata)
     return 1; /* error */
 
   form->data = formdata;
   form->sent = 0;
+  form->fp = NULL;
 
   return 0;
 }
 
-/* fread() emulation */
-int Curl_FormReader(char *buffer,
-                    size_t size,
-                    size_t nitems,
-                    FILE *mydata)
+static size_t readfromfile(struct Form *form, char *buffer, size_t size)
+{
+  size_t nread;
+  if(!form->fp) {
+    /* this file hasn't yet been opened */
+    form->fp = fopen(form->data->line, "rb"); /* b is for binary */
+    if(!form->fp)
+      return -1; /* failure */
+  }
+  nread = fread(buffer, 1, size, form->fp);
+
+  if(nread != size) {
+    /* this is the last chunk form the file, move on */
+    fclose(form->fp);
+    form->fp = NULL;
+    form->data = form->data->next;
+  }
+
+  return nread;
+}
+
+/*
+ * Curl_FormReader() is the fread() emulation function that will be used to
+ * deliver the formdata to the transfer loop and then sent away to the peer.
+ */
+size_t Curl_FormReader(char *buffer,
+                       size_t size,
+                       size_t nitems,
+                       FILE *mydata)
 {
   struct Form *form;
-  int wantedsize;
-  int gotsize = 0;
+  size_t wantedsize;
+  size_t gotsize = 0;
 
   form=(struct Form *)mydata;
 
-  wantedsize = (int)(size * nitems);
+  wantedsize = size * nitems;
 
   if(!form->data)
     return 0; /* nothing, error, empty */
 
+  if(form->data->type == FORM_FILE)
+    return readfromfile(form, buffer, wantedsize);
+
   do {
-  
+
     if( (form->data->length - form->sent ) > wantedsize - gotsize) {
 
       memcpy(buffer + gotsize , form->data->line + form->sent,
@@ -1342,61 +1245,38 @@ int Curl_FormReader(char *buffer,
            form->data->line + form->sent,
            (form->data->length - form->sent) );
     gotsize += form->data->length - form->sent;
-    
+
     form->sent = 0;
 
     form->data = form->data->next; /* advance */
 
-  } while(form->data);
+  } while(form->data && (form->data->type == FORM_DATA));
   /* If we got an empty line and we have more data, we proceed to the next
      line immediately to avoid returning zero before we've reached the end.
      This is the bug reported November 22 1999 on curl 6.3. (Daniel) */
 
   return gotsize;
 }
 
-/* possible (old) fread() emulation that copies at most one line */
-int Curl_FormReadOneLine(char *buffer,
-                         size_t size,
-                         size_t nitems,
-                         FILE *mydata)
+/*
+ * Curl_formpostheader() returns the first line of the formpost, the
+ * request-header part (which is not part of the request-body like the rest of
+ * the post).
+ */
+char *Curl_formpostheader(void *formp, size_t *len)
 {
-  struct Form *form;
-  int wantedsize;
-  int gotsize;
-
-  form=(struct Form *)mydata;
-
-  wantedsize = (int)(size * nitems);
+  char *header;
+  struct Form *form=(struct Form *)formp;
 
   if(!form->data)
-    return -1; /* nothing, error, empty */
-
-  do {
-  
-    if( (form->data->length - form->sent ) > wantedsize ) {
+    return 0; /* nothing, ERROR! */
 
-      memcpy(buffer, form->data->line + form->sent, wantedsize);
+  header = form->data->line;
+  *len = form->data->length;
 
-      form->sent += wantedsize;
+  form->data = form->data->next; /* advance */
 
-      return wantedsize;
-    }
-
-    memcpy(buffer,
-           form->data->line + form->sent,
-           gotsize = (form->data->length - form->sent) );
-
-    form->sent = 0;
-
-    form->data = form->data->next; /* advance */
-
-  } while(!gotsize && form->data);
-  /* If we got an empty line and we have more data, we proceed to the next
-     line immediately to avoid returning zero before we've reached the end.
-     This is the bug reported November 22 1999 on curl 6.3. (Daniel) */
-
-  return gotsize;
+  return header;
 }
 
 
@@ -1447,7 +1327,7 @@ int main()
   int value6length = strlen(value5);
   int errors = 0;
   int size;
-  int nread;
+  size_t nread;
   char buffer[4096];
   struct curl_httppost *httppost=NULL;
   struct curl_httppost *last_post=NULL;
@@ -1546,66 +1426,53 @@ int main()
 
 #endif
 
-#ifdef _OLD_FORM_DEBUG
-
-int main(int argc, char **argv)
+#else  /* CURL_DISABLE_HTTP */
+CURLFORMcode curl_formadd(struct curl_httppost **httppost,
+                          struct curl_httppost **last_post,
+                          ...)
 {
-#if 0
-  char *testargs[]={
-    "name1 = data in number one",
-    "name2 = number two data",
-    "test = @upload"
-  };
-#endif
-  int i;
-  char *nextarg;
-  struct curl_httppost *httppost=NULL;
-  struct curl_httppost *last_post=NULL;
-  struct curl_httppost *post;
-  int size;
-  int nread;
-  char buffer[4096];
-
-  struct FormData *form;
-  struct Form formread;
+  (void)httppost;
+  (void)last_post;
+  return CURL_FORMADD_DISABLED;
+}
 
-  for(i=1; i<argc; i++) {
+void curl_formfree(struct curl_httppost *form)
+{
+  (void)form;
+  /* does nothing HTTP is disabled */
+}
 
-    if( FormParse( argv[i],
-                   &httppost,
-                   &last_post)) {
-      fprintf(stderr, "Illegally formatted input field: '%s'!\n",
-              argv[i]);
-      return 1;
-    }
-  }
+#endif  /* CURL_DISABLE_HTTP */
 
-  form=Curl_getFormData(httppost, &size);
+/*
+ * Curl_FormBoundary() creates a suitable boundary string and returns an
+ * allocated one. This is also used by SSL-code so it must be present even
+ * if HTTP is disabled!
+ */
+char *Curl_FormBoundary(void)
+{
+  char *retstring;
+  static int randomizer=0; /* this is just so that two boundaries within
+                              the same form won't be identical */
+  size_t i;
 
-  Curl_FormInit(&formread, form);
+  static char table16[]="abcdef0123456789";
 
-  do {
-    nread = Curl_FormReader(buffer, 1, sizeof(buffer),
-                            (FILE *)&formread);
+  retstring = (char *)malloc(BOUNDARY_LENGTH+1);
 
-    if(-1 == nread)
-      break;
-    fwrite(buffer, nread, 1, stderr);
-  } while(1);
+  if(!retstring)
+    return NULL; /* failed */
 
-  fprintf(stderr, "size: %d\n", size);
+  srand(time(NULL)+randomizer++); /* seed */
 
-  return 0;
-}
+  strcpy(retstring, "----------------------------");
 
-#endif
+  for(i=strlen(retstring); i<BOUNDARY_LENGTH; i++)
+    retstring[i] = table16[rand()%16];
 
-#endif /* CURL_DISABLE_HTTP */
+  /* 28 dashes and 12 hexadecimal digits makes 12^16 (184884258895036416)
+     combinations */
+  retstring[BOUNDARY_LENGTH]=0; /* zero terminate */
 
-/*
- * local variables:
- * eval: (load-file "../curl-mode.el")
- * end:
- * vim600: fdm=marker
- * vim: et sw=2 ts=2 sts=2 tw=78
- */
+  return retstring;
+}
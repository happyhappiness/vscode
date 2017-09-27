         int is_remove;
         apr_xml_elem *prop_group;
         apr_xml_elem *one_prop;
 
         /* Ignore children that are not set/remove */
         if (child->ns != APR_XML_NS_DAV_ID
-            || (!(is_remove = strcmp(child->name, "remove") == 0)
+            || (!(is_remove = (strcmp(child->name, "remove") == 0))
                 && strcmp(child->name, "set") != 0)) {
             continue;
         }
 
         /* make sure that a "prop" child exists for set/remove */
         if ((prop_group = dav_find_child(child, "prop")) == NULL) {
             dav_close_propdb(propdb);
 
             /* undo any auto-checkout */
             dav_auto_checkin(r, resource, 1 /*undo*/, 0 /*unlock*/, &av_info);
 
             /* This supplies additional information for the default message. */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00588)
                           "A \"prop\" element is missing inside "
                           "the propertyupdate command.");
             return HTTP_BAD_REQUEST;
         }
 
         for (one_prop = prop_group->first_child; one_prop;

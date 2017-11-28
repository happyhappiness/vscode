 
         storeAppendPrintf(entry, "\n");
     }
 }
 
 static void
-freed_acl_tos(void *data)
-{
-    acl_tos *l = static_cast<acl_tos *>(data);
-    aclDestroyAclList(&l->aclList);
-}
-
-static void
 parse_acl_tos(acl_tos ** head)
 {
-    acl_tos *l;
-    acl_tos **tail = head;  /* sane name below */
     unsigned int tos;           /* Initially uint for strtoui. Casted to tos_t before return */
     char *token = ConfigParser::NextToken();
 
     if (!token) {
         self_destruct();
         return;

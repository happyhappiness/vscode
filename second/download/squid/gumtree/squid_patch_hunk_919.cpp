     }
     *s = '\0';
     return buf;
 }
 
 void *
-ACL::operator new (size_t byteCount)
+ACL::operator new (size_t)
 {
     fatal ("unusable ACL::new");
     return (void *)1;
 }
 
 void
-ACL::operator delete (void *address)
+ACL::operator delete (void *)
 {
     fatal ("unusable ACL::delete");
 }
 
 ACL *
 ACL::FindByName(const char *name)

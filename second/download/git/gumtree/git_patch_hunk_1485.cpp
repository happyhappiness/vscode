 
 /*
  * Returns the object, having parsed it to find out what it is.
  *
  * Returns NULL if the object is missing or corrupt.
  */
-struct object *parse_object(const unsigned char *sha1);
+struct object *parse_object(const struct object_id *oid);
 
 /*
  * Like parse_object, but will die() instead of returning NULL. If the
  * "name" parameter is not NULL, it is included in the error message
- * (otherwise, the sha1 hex is given).
+ * (otherwise, the hex object ID is given).
  */
-struct object *parse_object_or_die(const unsigned char *sha1, const char *name);
+struct object *parse_object_or_die(const struct object_id *oid, const char *name);
 
 /* Given the result of read_sha1_file(), returns the object after
  * parsing it.  eaten_p indicates if the object has a borrowed copy
  * of buffer and the caller should not free() it.
  */
-struct object *parse_object_buffer(const unsigned char *sha1, enum object_type type, unsigned long size, void *buffer, int *eaten_p);
+struct object *parse_object_buffer(const struct object_id *oid, enum object_type type, unsigned long size, void *buffer, int *eaten_p);
 
 /** Returns the object, with potentially excess memory allocated. **/
 struct object *lookup_unknown_object(const unsigned  char *sha1);
 
 struct object_list *object_list_insert(struct object *item,
 				       struct object_list **list_p);

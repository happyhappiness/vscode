 			return error("%s", message);
 		return -1;
 	}
 	return -1;
 }
 
-/* NEEDSWORK: give this a better name and share with tree-walk.c */
-static int name_compare(const char *a, int a_len,
-			const char *b, int b_len)
-{
-	int len = (a_len < b_len) ? a_len : b_len;
-	int cmp = memcmp(a, b, len);
-	if (cmp)
-		return cmp;
-	return (a_len - b_len);
-}
-
 /*
  * The tree traversal is looking at name p.  If we have a matching entry,
  * return it.  If name p is a directory in the index, do not return
  * anything, as we will want to match it when the traversal descends into
  * the directory.
  */

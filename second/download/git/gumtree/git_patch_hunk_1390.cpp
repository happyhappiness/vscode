 	if (!size)
 		goto free_return;
 	buf++; size--;
 	if (0 <= it->entry_count) {
 		if (size < 20)
 			goto free_return;
-		hashcpy(it->sha1, (const unsigned char*)buf);
+		hashcpy(it->oid.hash, (const unsigned char*)buf);
 		buf += 20;
 		size -= 20;
 	}
 
 #if DEBUG
 	if (0 <= it->entry_count)
 		fprintf(stderr, "cache-tree <%s> (%d ent, %d subtree) %s\n",
 			*buffer, it->entry_count, subtree_nr,
-			sha1_to_hex(it->sha1));
+			oid_to_hex(&it->oid));
 	else
 		fprintf(stderr, "cache-tree <%s> (%d subtrees) invalid\n",
 			*buffer, subtree_nr);
 #endif
 
 	/*

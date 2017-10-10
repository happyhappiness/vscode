 			continue;
 
 		error("pathspec '%s' did not match any file(s) known to git.",
 		      pathspec->items[num].original);
 		errors++;
 	}
-	strbuf_release(&sb);
 	return errors;
 }
 
 /*
  * Return the length of the "simple" part of a path match limiter.
  */

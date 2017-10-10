 		 */
 		if ((leading != frag->leading) ||
 		    (trailing != frag->trailing))
 			fprintf_ln(stderr, _("Context reduced to (%ld/%ld)"
 					     " to apply fragment at %d"),
 				   leading, trailing, applied_pos+1);
-		update_image(img, applied_pos, &preimage, &postimage);
+		update_image(state, img, applied_pos, &preimage, &postimage);
 	} else {
-		if (apply_verbosely)
+		if (state->apply_verbosely)
 			error(_("while searching for:\n%.*s"),
 			      (int)(old - oldlines), oldlines);
 	}
 
 out:
 	free(oldlines);

 				die(_("Commit %s does not have a GPG signature."), hex);
 			}
 			if (verbosity >= 0 && signature_check.result == 'G')
 				printf(_("Commit %s has a good GPG signature by %s\n"),
 				       hex, signature_check.signer);
 
-			free(signature_check.gpg_output);
-			free(signature_check.gpg_status);
-			free(signature_check.signer);
-			free(signature_check.key);
+			signature_check_clear(&signature_check);
 		}
 	}
 
 	strbuf_addstr(&buf, "merge");
 	for (p = remoteheads; p; p = p->next)
 		strbuf_addf(&buf, " %s", merge_remote_util(p->item)->name);

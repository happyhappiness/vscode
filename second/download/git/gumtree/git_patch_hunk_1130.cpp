 		warning(_("you may want to cleanup or recover these."));
 		exit(1);
 	} else
 		exit_cleanup(tmpdir, rc);
 
 finish:
+	if (fp)
+		fclose(fp);
+
 	free(lbase_dir);
 	free(rbase_dir);
 	strbuf_release(&ldir);
 	strbuf_release(&rdir);
 	strbuf_release(&wtdir);
 	strbuf_release(&buf);

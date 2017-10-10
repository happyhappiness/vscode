 		default:
 			die("BUG: unknown get_sha1_with_context result %d\n",
 			       result);
 			break;
 		}
 		fflush(stdout);
-		return 0;
+		return;
 	}
 
 	if (ctx.mode == 0) {
 		printf("symlink %"PRIuMAX"\n%s\n",
 		       (uintmax_t)ctx.symlink_path.len,
 		       ctx.symlink_path.buf);
 		fflush(stdout);
-		return 0;
+		return;
 	}
 
-	if (sha1_object_info_extended(data->sha1, &data->info, LOOKUP_REPLACE_OBJECT) < 0) {
-		printf("%s missing\n", obj_name);
-		fflush(stdout);
-		return 0;
-	}
+	batch_object_write(obj_name, opt, data);
+}
 
-	strbuf_expand(&buf, opt->format, expand_format, data);
-	strbuf_addch(&buf, '\n');
-	write_or_die(1, buf.buf, buf.len);
-	strbuf_release(&buf);
+struct object_cb_data {
+	struct batch_options *opt;
+	struct expand_data *expand;
+};
 
-	if (opt->print_contents) {
-		print_object_or_die(1, data);
-		write_or_die(1, "\n", 1);
-	}
+static void batch_object_cb(const unsigned char sha1[20], void *vdata)
+{
+	struct object_cb_data *data = vdata;
+	hashcpy(data->expand->sha1, sha1);
+	batch_object_write(NULL, data->opt, data->expand);
+}
+
+static int batch_loose_object(const unsigned char *sha1,
+			      const char *path,
+			      void *data)
+{
+	sha1_array_append(data, sha1);
+	return 0;
+}
+
+static int batch_packed_object(const unsigned char *sha1,
+			       struct packed_git *pack,
+			       uint32_t pos,
+			       void *data)
+{
+	sha1_array_append(data, sha1);
 	return 0;
 }
 
 static int batch_objects(struct batch_options *opt)
 {
 	struct strbuf buf = STRBUF_INIT;

 		atom->u.if_then_else.cmp_status = COMPARE_UNEQUAL;
 	} else {
 		die(_("unrecognized %%(if) argument: %s"), arg);
 	}
 }
 
+static void head_atom_parser(struct used_atom *atom, const char *arg)
+{
+	unsigned char unused[GIT_SHA1_RAWSZ];
+
+	atom->u.head = resolve_refdup("HEAD", RESOLVE_REF_READING, unused, NULL);
+}
 
 static struct {
 	const char *name;
 	cmp_type cmp_type;
 	void (*parser)(struct used_atom *atom, const char *arg);
 } valid_atom[] = {

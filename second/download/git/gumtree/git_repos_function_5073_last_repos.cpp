static void set_refspecs(const char **refs, int nr, const char *repo)
{
	struct remote *remote = NULL;
	struct ref *local_refs = NULL;
	int i;

	for (i = 0; i < nr; i++) {
		const char *ref = refs[i];
		if (!strcmp("tag", ref)) {
			struct strbuf tagref = STRBUF_INIT;
			if (nr <= ++i)
				die(_("tag shorthand without <tag>"));
			ref = refs[i];
			if (deleterefs)
				strbuf_addf(&tagref, ":refs/tags/%s", ref);
			else
				strbuf_addf(&tagref, "refs/tags/%s", ref);
			ref = strbuf_detach(&tagref, NULL);
		} else if (deleterefs) {
			struct strbuf delref = STRBUF_INIT;
			if (strchr(ref, ':'))
				die(_("--delete only accepts plain target ref names"));
			strbuf_addf(&delref, ":%s", ref);
			ref = strbuf_detach(&delref, NULL);
		} else if (!strchr(ref, ':')) {
			if (!remote) {
				/* lazily grab remote and local_refs */
				remote = remote_get(repo);
				local_refs = get_local_heads();
			}
			ref = map_refspec(ref, remote, local_refs);
		}
		add_refspec(ref);
	}
}
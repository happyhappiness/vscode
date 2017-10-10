 *
 * If the strbuf ends with a newline, the output printed by
 * graph_show_commit_msg() will end with a newline.  If the strbuf is
 * missing a terminating newline (including if it is empty), the output
 * printed by graph_show_commit_msg() will also be missing a terminating
 * newline.
 *
 * Note that unlike some other graph display functions, you must pass the file
 * handle directly. It is assumed that this is the same file handle as the
 * file specified by the graph diff options. This is necessary so that
 * graph_show_commit_msg can be called even with a NULL graph.
 */
void graph_show_commit_msg(struct git_graph *graph,
			   FILE *file,
			   struct strbuf const *sb);

#endif /* GRAPH_H */

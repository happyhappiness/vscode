 	xch->ignore = 0;
 
 	return xch;
 }
 
 
-static int is_blank_line(xrecord_t **recs, long ix, long flags)
+static int is_blank_line(xrecord_t *rec, long flags)
 {
-	return xdl_blankline(recs[ix]->ptr, recs[ix]->size, flags);
+	return xdl_blankline(rec->ptr, rec->size, flags);
 }
 
-static int recs_match(xrecord_t **recs, long ixs, long ix, long flags)
+static int recs_match(xrecord_t *rec1, xrecord_t *rec2, long flags)
 {
-	return (recs[ixs]->ha == recs[ix]->ha &&
-		xdl_recmatch(recs[ixs]->ptr, recs[ixs]->size,
-			     recs[ix]->ptr, recs[ix]->size,
+	return (rec1->ha == rec2->ha &&
+		xdl_recmatch(rec1->ptr, rec1->size,
+			     rec2->ptr, rec2->size,
 			     flags));
 }
 
-int xdl_change_compact(xdfile_t *xdf, xdfile_t *xdfo, long flags) {
-	long ix, ixo, ixs, ixref, grpsiz, nrec = xdf->nrec;
-	char *rchg = xdf->rchg, *rchgo = xdfo->rchg;
-	unsigned int blank_lines;
-	xrecord_t **recs = xdf->recs;
+/*
+ * If a line is indented more than this, get_indent() just returns this value.
+ * This avoids having to do absurd amounts of work for data that are not
+ * human-readable text, and also ensures that the output of get_indent fits within
+ * an int.
+ */
+#define MAX_INDENT 200
+
+/*
+ * Return the amount of indentation of the specified line, treating TAB as 8
+ * columns. Return -1 if line is empty or contains only whitespace. Clamp the
+ * output value at MAX_INDENT.
+ */
+static int get_indent(xrecord_t *rec)
+{
+	long i;
+	int ret = 0;
+
+	for (i = 0; i < rec->size; i++) {
+		char c = rec->ptr[i];
+
+		if (!XDL_ISSPACE(c))
+			return ret;
+		else if (c == ' ')
+			ret += 1;
+		else if (c == '\t')
+			ret += 8 - ret % 8;
+		/* ignore other whitespace characters */
+
+		if (ret >= MAX_INDENT)
+			return MAX_INDENT;
+	}
+
+	/* The line contains only whitespace. */
+	return -1;
+}
 
+/*
+ * If more than this number of consecutive blank rows are found, just return this
+ * value. This avoids requiring O(N^2) work for pathological cases, and also
+ * ensures that the output of score_split fits in an int.
+ */
+#define MAX_BLANKS 20
+
+/* Characteristics measured about a hypothetical split position. */
+struct split_measurement {
 	/*
-	 * This is the same of what GNU diff does. Move back and forward
-	 * change groups for a consistent and pretty diff output. This also
-	 * helps in finding joinable change groups and reduce the diff size.
+	 * Is the split at the end of the file (aside from any blank lines)?
 	 */
-	for (ix = ixo = 0;;) {
-		/*
-		 * Find the first changed line in the to-be-compacted file.
-		 * We need to keep track of both indexes, so if we find a
-		 * changed lines group on the other file, while scanning the
-		 * to-be-compacted file, we need to skip it properly. Note
-		 * that loops that are testing for changed lines on rchg* do
-		 * not need index bounding since the array is prepared with
-		 * a zero at position -1 and N.
-		 */
-		for (; ix < nrec && !rchg[ix]; ix++)
-			while (rchgo[ixo++]);
-		if (ix == nrec)
+	int end_of_file;
+
+	/*
+	 * How much is the line immediately following the split indented (or -1 if
+	 * the line is blank):
+	 */
+	int indent;
+
+	/*
+	 * How many consecutive lines above the split are blank?
+	 */
+	int pre_blank;
+
+	/*
+	 * How much is the nearest non-blank line above the split indented (or -1
+	 * if there is no such line)?
+	 */
+	int pre_indent;
+
+	/*
+	 * How many lines after the line following the split are blank?
+	 */
+	int post_blank;
+
+	/*
+	 * How much is the nearest non-blank line after the line following the
+	 * split indented (or -1 if there is no such line)?
+	 */
+	int post_indent;
+};
+
+struct split_score {
+	/* The effective indent of this split (smaller is preferred). */
+	int effective_indent;
+
+	/* Penalty for this split (smaller is preferred). */
+	int penalty;
+};
+
+/*
+ * Fill m with information about a hypothetical split of xdf above line split.
+ */
+static void measure_split(const xdfile_t *xdf, long split,
+			  struct split_measurement *m)
+{
+	long i;
+
+	if (split >= xdf->nrec) {
+		m->end_of_file = 1;
+		m->indent = -1;
+	} else {
+		m->end_of_file = 0;
+		m->indent = get_indent(xdf->recs[split]);
+	}
+
+	m->pre_blank = 0;
+	m->pre_indent = -1;
+	for (i = split - 1; i >= 0; i--) {
+		m->pre_indent = get_indent(xdf->recs[i]);
+		if (m->pre_indent != -1)
+			break;
+		m->pre_blank += 1;
+		if (m->pre_blank == MAX_BLANKS) {
+			m->pre_indent = 0;
+			break;
+		}
+	}
+
+	m->post_blank = 0;
+	m->post_indent = -1;
+	for (i = split + 1; i < xdf->nrec; i++) {
+		m->post_indent = get_indent(xdf->recs[i]);
+		if (m->post_indent != -1)
 			break;
+		m->post_blank += 1;
+		if (m->post_blank == MAX_BLANKS) {
+			m->post_indent = 0;
+			break;
+		}
+	}
+}
 
+/*
+ * The empirically-determined weight factors used by score_split() below.
+ * Larger values means that the position is a less favorable place to split.
+ *
+ * Note that scores are only ever compared against each other, so multiplying
+ * all of these weight/penalty values by the same factor wouldn't change the
+ * heuristic's behavior. Still, we need to set that arbitrary scale *somehow*.
+ * In practice, these numbers are chosen to be large enough that they can be
+ * adjusted relative to each other with sufficient precision despite using
+ * integer math.
+ */
+
+/* Penalty if there are no non-blank lines before the split */
+#define START_OF_FILE_PENALTY 1
+
+/* Penalty if there are no non-blank lines after the split */
+#define END_OF_FILE_PENALTY 21
+
+/* Multiplier for the number of blank lines around the split */
+#define TOTAL_BLANK_WEIGHT (-30)
+
+/* Multiplier for the number of blank lines after the split */
+#define POST_BLANK_WEIGHT 6
+
+/*
+ * Penalties applied if the line is indented more than its predecessor
+ */
+#define RELATIVE_INDENT_PENALTY (-4)
+#define RELATIVE_INDENT_WITH_BLANK_PENALTY 10
+
+/*
+ * Penalties applied if the line is indented less than both its predecessor and
+ * its successor
+ */
+#define RELATIVE_OUTDENT_PENALTY 24
+#define RELATIVE_OUTDENT_WITH_BLANK_PENALTY 17
+
+/*
+ * Penalties applied if the line is indented less than its predecessor but not
+ * less than its successor
+ */
+#define RELATIVE_DEDENT_PENALTY 23
+#define RELATIVE_DEDENT_WITH_BLANK_PENALTY 17
+
+/*
+ * We only consider whether the sum of the effective indents for splits are
+ * less than (-1), equal to (0), or greater than (+1) each other. The resulting
+ * value is multiplied by the following weight and combined with the penalty to
+ * determine the better of two scores.
+ */
+#define INDENT_WEIGHT 60
+
+/*
+ * Compute a badness score for the hypothetical split whose measurements are
+ * stored in m. The weight factors were determined empirically using the tools and
+ * corpus described in
+ *
+ *     https://github.com/mhagger/diff-slider-tools
+ *
+ * Also see that project if you want to improve the weights based on, for example,
+ * a larger or more diverse corpus.
+ */
+static void score_add_split(const struct split_measurement *m, struct split_score *s)
+{
+	/*
+	 * A place to accumulate penalty factors (positive makes this index more
+	 * favored):
+	 */
+	int post_blank, total_blank, indent, any_blanks;
+
+	if (m->pre_indent == -1 && m->pre_blank == 0)
+		s->penalty += START_OF_FILE_PENALTY;
+
+	if (m->end_of_file)
+		s->penalty += END_OF_FILE_PENALTY;
+
+	/*
+	 * Set post_blank to the number of blank lines following the split,
+	 * including the line immediately after the split:
+	 */
+	post_blank = (m->indent == -1) ? 1 + m->post_blank : 0;
+	total_blank = m->pre_blank + post_blank;
+
+	/* Penalties based on nearby blank lines: */
+	s->penalty += TOTAL_BLANK_WEIGHT * total_blank;
+	s->penalty += POST_BLANK_WEIGHT * post_blank;
+
+	if (m->indent != -1)
+		indent = m->indent;
+	else
+		indent = m->post_indent;
+
+	any_blanks = (total_blank != 0);
+
+	/* Note that the effective indent is -1 at the end of the file: */
+	s->effective_indent += indent;
+
+	if (indent == -1) {
+		/* No additional adjustments needed. */
+	} else if (m->pre_indent == -1) {
+		/* No additional adjustments needed. */
+	} else if (indent > m->pre_indent) {
+		/*
+		 * The line is indented more than its predecessor.
+		 */
+		s->penalty += any_blanks ?
+			RELATIVE_INDENT_WITH_BLANK_PENALTY :
+			RELATIVE_INDENT_PENALTY;
+	} else if (indent == m->pre_indent) {
+		/*
+		 * The line has the same indentation level as its predecessor.
+		 * No additional adjustments needed.
+		 */
+	} else {
 		/*
-		 * Record the start of a changed-group in the to-be-compacted file
-		 * and find the end of it, on both to-be-compacted and other file
-		 * indexes (ix and ixo).
+		 * The line is indented less than its predecessor. It could be
+		 * the block terminator of the previous block, but it could
+		 * also be the start of a new block (e.g., an "else" block, or
+		 * maybe the previous block didn't have a block terminator).
+		 * Try to distinguish those cases based on what comes next:
 		 */
-		ixs = ix;
-		for (ix++; rchg[ix]; ix++);
-		for (; rchgo[ixo]; ixo++);
+		if (m->post_indent != -1 && m->post_indent > indent) {
+			/*
+			 * The following line is indented more. So it is likely
+			 * that this line is the start of a block.
+			 */
+			s->penalty += any_blanks ?
+				RELATIVE_OUTDENT_WITH_BLANK_PENALTY :
+				RELATIVE_OUTDENT_PENALTY;
+		} else {
+			/*
+			 * That was probably the end of a block.
+			 */
+			s->penalty += any_blanks ?
+				RELATIVE_DEDENT_WITH_BLANK_PENALTY :
+				RELATIVE_DEDENT_PENALTY;
+		}
+	}
+}
+
+static int score_cmp(struct split_score *s1, struct split_score *s2)
+{
+	/* -1 if s1.effective_indent < s2->effective_indent, etc. */
+	int cmp_indents = ((s1->effective_indent > s2->effective_indent) -
+			   (s1->effective_indent < s2->effective_indent));
+
+	return INDENT_WEIGHT * cmp_indents + (s1->penalty - s2->penalty);
+}
+
+/*
+ * Represent a group of changed lines in an xdfile_t (i.e., a contiguous group
+ * of lines that was inserted or deleted from the corresponding version of the
+ * file). We consider there to be such a group at the beginning of the file, at
+ * the end of the file, and between any two unchanged lines, though most such
+ * groups will usually be empty.
+ *
+ * If the first line in a group is equal to the line following the group, then
+ * the group can be slid down. Similarly, if the last line in a group is equal
+ * to the line preceding the group, then the group can be slid up. See
+ * group_slide_down() and group_slide_up().
+ *
+ * Note that loops that are testing for changed lines in xdf->rchg do not need
+ * index bounding since the array is prepared with a zero at position -1 and N.
+ */
+struct xdlgroup {
+	/*
+	 * The index of the first changed line in the group, or the index of
+	 * the unchanged line above which the (empty) group is located.
+	 */
+	long start;
 
+	/*
+	 * The index of the first unchanged line after the group. For an empty
+	 * group, end is equal to start.
+	 */
+	long end;
+};
+
+/*
+ * Initialize g to point at the first group in xdf.
+ */
+static void group_init(xdfile_t *xdf, struct xdlgroup *g)
+{
+	g->start = g->end = 0;
+	while (xdf->rchg[g->end])
+		g->end++;
+}
+
+/*
+ * Move g to describe the next (possibly empty) group in xdf and return 0. If g
+ * is already at the end of the file, do nothing and return -1.
+ */
+static inline int group_next(xdfile_t *xdf, struct xdlgroup *g)
+{
+	if (g->end == xdf->nrec)
+		return -1;
+
+	g->start = g->end + 1;
+	for (g->end = g->start; xdf->rchg[g->end]; g->end++)
+		;
+
+	return 0;
+}
+
+/*
+ * Move g to describe the previous (possibly empty) group in xdf and return 0.
+ * If g is already at the beginning of the file, do nothing and return -1.
+ */
+static inline int group_previous(xdfile_t *xdf, struct xdlgroup *g)
+{
+	if (g->start == 0)
+		return -1;
+
+	g->end = g->start - 1;
+	for (g->start = g->end; xdf->rchg[g->start - 1]; g->start--)
+		;
+
+	return 0;
+}
+
+/*
+ * If g can be slid toward the end of the file, do so, and if it bumps into a
+ * following group, expand this group to include it. Return 0 on success or -1
+ * if g cannot be slid down.
+ */
+static int group_slide_down(xdfile_t *xdf, struct xdlgroup *g, long flags)
+{
+	if (g->end < xdf->nrec &&
+	    recs_match(xdf->recs[g->start], xdf->recs[g->end], flags)) {
+		xdf->rchg[g->start++] = 0;
+		xdf->rchg[g->end++] = 1;
+
+		while (xdf->rchg[g->end])
+			g->end++;
+
+		return 0;
+	} else {
+		return -1;
+	}
+}
+
+/*
+ * If g can be slid toward the beginning of the file, do so, and if it bumps
+ * into a previous group, expand this group to include it. Return 0 on success
+ * or -1 if g cannot be slid up.
+ */
+static int group_slide_up(xdfile_t *xdf, struct xdlgroup *g, long flags)
+{
+	if (g->start > 0 &&
+	    recs_match(xdf->recs[g->start - 1], xdf->recs[g->end - 1], flags)) {
+		xdf->rchg[--g->start] = 1;
+		xdf->rchg[--g->end] = 0;
+
+		while (xdf->rchg[g->start - 1])
+			g->start--;
+
+		return 0;
+	} else {
+		return -1;
+	}
+}
+
+static void xdl_bug(const char *msg)
+{
+	fprintf(stderr, "BUG: %s\n", msg);
+	exit(1);
+}
+
+/*
+ * Move back and forward change groups for a consistent and pretty diff output.
+ * This also helps in finding joinable change groups and reducing the diff
+ * size.
+ */
+int xdl_change_compact(xdfile_t *xdf, xdfile_t *xdfo, long flags) {
+	struct xdlgroup g, go;
+	long earliest_end, end_matching_other;
+	long groupsize;
+	unsigned int blank_lines;
+
+	group_init(xdf, &g);
+	group_init(xdfo, &go);
+
+	while (1) {
+		/* If the group is empty in the to-be-compacted file, skip it: */
+		if (g.end == g.start)
+			goto next;
+
+		/*
+		 * Now shift the change up and then down as far as possible in
+		 * each direction. If it bumps into any other changes, merge them.
+		 */
 		do {
-			grpsiz = ix - ixs;
-			blank_lines = 0;
+			groupsize = g.end - g.start;
 
 			/*
-			 * If the line before the current change group, is equal to
-			 * the last line of the current change group, shift backward
-			 * the group.
-			 */
-			while (ixs > 0 && recs_match(recs, ixs - 1, ix - 1, flags)) {
-				rchg[--ixs] = 1;
-				rchg[--ix] = 0;
-
-				/*
-				 * This change might have joined two change groups,
-				 * so we try to take this scenario in account by moving
-				 * the start index accordingly (and so the other-file
-				 * end-of-group index).
-				 */
-				for (; rchg[ixs - 1]; ixs--);
-				while (rchgo[--ixo]);
-			}
+			 * Keep track of the last "end" index that causes this
+			 * group to align with a group of changed lines in the
+			 * other file. -1 indicates that we haven't found such
+			 * a match yet:
+			 */
+			end_matching_other = -1;
 
 			/*
-			 * Record the end-of-group position in case we are matched
-			 * with a group of changes in the other file (that is, the
-			 * change record before the end-of-group index in the other
-			 * file is set).
-			 */
-			ixref = rchgo[ixo - 1] ? ix: nrec;
-
-			/*
-			 * If the first line of the current change group, is equal to
-			 * the line next of the current change group, shift forward
-			 * the group.
-			 */
-			while (ix < nrec && recs_match(recs, ixs, ix, flags)) {
-				blank_lines += is_blank_line(recs, ix, flags);
-
-				rchg[ixs++] = 0;
-				rchg[ix++] = 1;
-
-				/*
-				 * This change might have joined two change groups,
-				 * so we try to take this scenario in account by moving
-				 * the start index accordingly (and so the other-file
-				 * end-of-group index). Keep tracking the reference
-				 * index in case we are shifting together with a
-				 * corresponding group of changes in the other file.
-				 */
-				for (; rchg[ix]; ix++);
-				while (rchgo[++ixo])
-					ixref = ix;
-			}
-		} while (grpsiz != ix - ixs);
+			 * Boolean value that records whether there are any blank
+			 * lines that could be made to be the last line of this
+			 * group.
+			 */
+			blank_lines = 0;
 
-		/*
-		 * Try to move back the possibly merged group of changes, to match
-		 * the recorded position in the other file.
-		 */
-		while (ixref < ix) {
-			rchg[--ixs] = 1;
-			rchg[--ix] = 0;
-			while (rchgo[--ixo]);
-		}
+			/* Shift the group backward as much as possible: */
+			while (!group_slide_up(xdf, &g, flags))
+				if (group_previous(xdfo, &go))
+					xdl_bug("group sync broken sliding up");
+
+			/*
+			 * This is this highest that this group can be shifted.
+			 * Record its end index:
+			 */
+			earliest_end = g.end;
+
+			if (go.end > go.start)
+				end_matching_other = g.end;
+
+			/* Now shift the group forward as far as possible: */
+			while (1) {
+				if (!blank_lines)
+					blank_lines = is_blank_line(
+							xdf->recs[g.end - 1],
+							flags);
+
+				if (group_slide_down(xdf, &g, flags))
+					break;
+				if (group_next(xdfo, &go))
+					xdl_bug("group sync broken sliding down");
+
+				if (go.end > go.start)
+					end_matching_other = g.end;
+			}
+		} while (groupsize != g.end - g.start);
 
 		/*
-		 * If a group can be moved back and forth, see if there is a
-		 * blank line in the moving space. If there is a blank line,
-		 * make sure the last blank line is the end of the group.
+		 * If the group can be shifted, then we can possibly use this
+		 * freedom to produce a more intuitive diff.
 		 *
-		 * As we already shifted the group forward as far as possible
-		 * in the earlier loop, we need to shift it back only if at all.
+		 * The group is currently shifted as far down as possible, so the
+		 * heuristics below only have to handle upwards shifts.
 		 */
-		if ((flags & XDF_COMPACTION_HEURISTIC) && blank_lines) {
-			while (ixs > 0 &&
-			       !is_blank_line(recs, ix - 1, flags) &&
-			       recs_match(recs, ixs - 1, ix - 1, flags)) {
-				rchg[--ixs] = 1;
-				rchg[--ix] = 0;
+
+		if (g.end == earliest_end) {
+			/* no shifting was possible */
+		} else if (end_matching_other != -1) {
+			/*
+			 * Move the possibly merged group of changes back to line
+			 * up with the last group of changes from the other file
+			 * that it can align with.
+			 */
+			while (go.end == go.start) {
+				if (group_slide_up(xdf, &g, flags))
+					xdl_bug("match disappeared");
+				if (group_previous(xdfo, &go))
+					xdl_bug("group sync broken sliding to match");
+			}
+		} else if ((flags & XDF_COMPACTION_HEURISTIC) && blank_lines) {
+			/*
+			 * Compaction heuristic: if it is possible to shift the
+			 * group to make its bottom line a blank line, do so.
+			 *
+			 * As we already shifted the group forward as far as
+			 * possible in the earlier loop, we only need to handle
+			 * backward shifts, not forward ones.
+			 */
+			while (!is_blank_line(xdf->recs[g.end - 1], flags)) {
+				if (group_slide_up(xdf, &g, flags))
+					xdl_bug("blank line disappeared");
+				if (group_previous(xdfo, &go))
+					xdl_bug("group sync broken sliding to blank line");
+			}
+		} else if (flags & XDF_INDENT_HEURISTIC) {
+			/*
+			 * Indent heuristic: a group of pure add/delete lines
+			 * implies two splits, one between the end of the "before"
+			 * context and the start of the group, and another between
+			 * the end of the group and the beginning of the "after"
+			 * context. Some splits are aesthetically better and some
+			 * are worse. We compute a badness "score" for each split,
+			 * and add the scores for the two splits to define a
+			 * "score" for each position that the group can be shifted
+			 * to. Then we pick the shift with the lowest score.
+			 */
+			long shift, best_shift = -1;
+			struct split_score best_score;
+
+			for (shift = earliest_end; shift <= g.end; shift++) {
+				struct split_measurement m;
+				struct split_score score = {0, 0};
+
+				measure_split(xdf, shift, &m);
+				score_add_split(&m, &score);
+				measure_split(xdf, shift - groupsize, &m);
+				score_add_split(&m, &score);
+				if (best_shift == -1 ||
+				    score_cmp(&score, &best_score) <= 0) {
+					best_score.effective_indent = score.effective_indent;
+					best_score.penalty = score.penalty;
+					best_shift = shift;
+				}
+			}
+
+			while (g.end > best_shift) {
+				if (group_slide_up(xdf, &g, flags))
+					xdl_bug("best shift unreached");
+				if (group_previous(xdfo, &go))
+					xdl_bug("group sync broken sliding to blank line");
 			}
 		}
+
+	next:
+		/* Move past the just-processed group: */
+		if (group_next(xdf, &g))
+			break;
+		if (group_next(xdfo, &go))
+			xdl_bug("group sync broken moving to next group");
 	}
 
+	if (!group_next(xdfo, &go))
+		xdl_bug("group sync broken at end of file");
+
 	return 0;
 }
 
 
 int xdl_build_script(xdfenv_t *xe, xdchange_t **xscr) {
 	xdchange_t *cscr = NULL, *xch;

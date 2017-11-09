static void free_diff_words_data(struct emit_callback *ecbdata)
{
	if (ecbdata->diff_words) {
		diff_words_flush(ecbdata);
		free (ecbdata->diff_words->opt);
		free (ecbdata->diff_words->minus.text.ptr);
		free (ecbdata->diff_words->minus.orig);
		free (ecbdata->diff_words->plus.text.ptr);
		free (ecbdata->diff_words->plus.orig);
		if (ecbdata->diff_words->word_regex) {
			regfree(ecbdata->diff_words->word_regex);
			free(ecbdata->diff_words->word_regex);
		}
		FREE_AND_NULL(ecbdata->diff_words);
	}
}
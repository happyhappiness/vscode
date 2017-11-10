static void diff_words_flush(struct emit_callback *ecbdata)
{
	if (ecbdata->diff_words->minus.text.size ||
	    ecbdata->diff_words->plus.text.size)
		diff_words_show(ecbdata->diff_words);
}
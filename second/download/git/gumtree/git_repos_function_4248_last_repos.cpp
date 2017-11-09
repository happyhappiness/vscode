static int score_missing(unsigned mode, const char *path)
{
	int score;

	if (S_ISDIR(mode))
		score = -1000;
	else if (S_ISLNK(mode))
		score = -500;
	else
		score = -50;
	return score;
}
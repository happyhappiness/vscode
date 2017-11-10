static int score_differs(unsigned mode1, unsigned mode2, const char *path)
{
	int score;

	if (S_ISDIR(mode1) != S_ISDIR(mode2))
		score = -100;
	else if (S_ISLNK(mode1) != S_ISLNK(mode2))
		score = -50;
	else
		score = -5;
	return score;
}
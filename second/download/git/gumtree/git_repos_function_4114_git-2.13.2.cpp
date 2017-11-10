static int score_matches(unsigned mode1, unsigned mode2, const char *path)
{
	int score;

	/* Heh, we found SHA-1 collisions between different kind of objects */
	if (S_ISDIR(mode1) != S_ISDIR(mode2))
		score = -100;
	else if (S_ISLNK(mode1) != S_ISLNK(mode2))
		score = -50;

	else if (S_ISDIR(mode1))
		score = 1000;
	else if (S_ISLNK(mode1))
		score = 500;
	else
		score = 250;
	return score;
}
int main(int argc, char *argv[])
{
	int n, i;
	gid_t list[NGROUPS];

	if ((n = getgroups(NGROUPS, list)) == -1) {
		perror("getgroups");
		return 1;
	}

	for (i = 0; i < n; i++) 
		printf("%u ", list[i]);
	printf("\n");
		
	return 0;
}
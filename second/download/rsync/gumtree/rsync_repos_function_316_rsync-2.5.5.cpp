static int count_args(char const **argv)
{
        int i = 0;

        while (argv[i] != NULL)
                i++;
        
        return i;
}
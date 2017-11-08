static void getrnge(char *str, step_vars_storage *vars)
{
    vars->low = *str++ & 0377;
    vars->size = ((*str & 0377) == 255)? 20000: (*str &0377) - vars->low;
}
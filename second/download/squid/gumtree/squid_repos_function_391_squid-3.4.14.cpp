void
Checktimer()
{
    static time_t Lasttime;	/* The last time the timer was checked */
    static time_t Currenttime;	/* The current time */

    Currenttime = time(NULL);

    /* If timeout has expired, check the denied user file, else return */
    if (difftime(Currenttime, Lasttime) < 60)
        return;
    else {
        Check_forchange(-1);
        Lasttime = Currenttime;
    }
}
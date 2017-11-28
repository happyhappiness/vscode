int
RFCNB_Discard_Rest(struct RFCNB_Con *con, int len)
{
    char temp[100];             /* Read into here */
    int rest, this_read, bytes_read;

    /* len is the amount we should read */

#ifdef RFCNB_DEBUG
    fprintf(stderr, "Discard_Rest called to discard: %i\n", len);
#endif

    rest = len;

    while (rest > 0) {

        this_read = (rest > sizeof(temp) ? sizeof(temp) : rest);

        bytes_read = read(con->fd, temp, this_read);

        if (bytes_read <= 0) {  /* Error so return */

            if (bytes_read < 0)
                RFCNB_errno = RFCNBE_BadRead;
            else
                RFCNB_errno = RFCNBE_ConGone;

            RFCNB_saved_errno = errno;
            return (RFCNBE_Bad);

        }
        rest = rest - bytes_read;

    }

    return (0);

}
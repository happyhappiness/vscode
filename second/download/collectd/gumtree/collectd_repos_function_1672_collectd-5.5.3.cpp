static int ted_read_value(double *ret_power, double *ret_voltage)
{
    unsigned char receive_buffer[300];
    unsigned char package_buffer[300];
    char pkt_request[1] = {0xAA};
    int package_buffer_pos;

    fd_set input;
    struct timeval timeout;

    int end_flag;
    int escape_flag;

    int status;

    assert (fd >= 0);

    /* Initialize the input set*/
    FD_ZERO (&input);
    FD_SET (fd, &input);

    /* Initialize timeout structure, set to 2 seconds */
    memset (&timeout, 0, sizeof (timeout));
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    /* clear out anything in the buffer */
    tcflush (fd, TCIFLUSH);

    status = write (fd, pkt_request, sizeof(pkt_request));
    if (status <= 0)
    {
        ERROR ("ted plugin: swrite failed.");
        return (-1);
    }

    /* Loop until we find the end of the package */
    end_flag = 0;
    package_buffer_pos = 0;
    while (end_flag == 0)
    {
        ssize_t receive_buffer_length;
        ssize_t i;

        /* check for timeout or input error*/
        status = select (fd + 1, &input, NULL, NULL, &timeout);
        if (status == 0) /* Timeout */
        {
            WARNING ("ted plugin: Timeout while waiting for file descriptor "
                    "to become ready.");
            return (-1);
        }
        else if ((status < 0) && ((errno == EAGAIN) || (errno == EINTR)))
        {
            /* Some signal or something. Start over.. */
            continue;
        }
        else if (status < 0)
        {
            char errbuf[1024];
            ERROR ("ted plugin: select failed: %s",
                    sstrerror (errno, errbuf, sizeof (errbuf)));
            return (-1);
        }

        receive_buffer_length = read (fd, receive_buffer, sizeof (receive_buffer));
        if (receive_buffer_length < 0)
        {
            char errbuf[1024];
            if ((errno == EAGAIN) || (errno == EINTR))
                continue;
            ERROR ("ted plugin: read(2) failed: %s",
                    sstrerror (errno, errbuf, sizeof (errbuf)));
            return (-1);
        }
        else if (receive_buffer_length == 0)
        {
            /* Should we close the FD in this case? */
            WARNING ("ted plugin: Received EOF from file descriptor.");
            return (-1);
        }
        else if (receive_buffer_length > sizeof (receive_buffer))
        {
            ERROR ("ted plugin: read(2) returned invalid value %zi.",
                    receive_buffer_length);
            return (-1);
        }

        /*
         * packet filter loop
         *
         * Handle escape sequences in `receive_buffer' and put the
         * result in `package_buffer'.
         */
        /* We need to see the begin sequence first. When we receive `ESCAPE
         * PKT_BEGIN', we set `package_buffer_pos' to zero to signal that
         * the beginning of the package has been found. */

        escape_flag = 0;
        for (i = 0; i < receive_buffer_length; i++)
        {
            /* Check if previous byte was the escape byte. */
            if (escape_flag == 1)
            {
                escape_flag = 0;
                /* escape escape = single escape */
                if ((receive_buffer[i] == ESCAPE)
                        && (package_buffer_pos >= 0))
                {
                    package_buffer[package_buffer_pos] = ESCAPE;
                    package_buffer_pos++;
                }
                else if (receive_buffer[i] == PKT_BEGIN)
                {
                    package_buffer_pos = 0;
                }
                else if  (receive_buffer[i] == PKT_END)
                {
                    end_flag = 1;
                    break;
                }
                else
                {
                    DEBUG ("ted plugin: Unknown escaped byte: %#x",
                            (unsigned int) receive_buffer[i]);
                }
            }
            else if (receive_buffer[i] == ESCAPE)
            {
                escape_flag = 1;
            }
            /* if we are in a package add byte to buffer
             * otherwise throw away */
            else if (package_buffer_pos >= 0)
            {
                package_buffer[package_buffer_pos] = receive_buffer[i];
                package_buffer_pos++;
            }
        } /* for (i = 0; i < receive_buffer_length; i++) */
    } /* while (end_flag == 0) */

    /* Check for errors inside the loop. */
    if ((end_flag == 0) || (package_buffer_pos != EXPECTED_PACKAGE_LENGTH))
        return (-1);

    /*
     * Power is at positions 247 and 248 (LSB first) in [10kW].
     * Voltage is at positions 251 and 252 (LSB first) in [.1V].
     *
     * Power is in 10 Watt steps
     * Voltage is in volts
     */
    *ret_power = 10.0 * (double) ((((int) package_buffer[248]) * 256)
            + ((int) package_buffer[247]));
    *ret_voltage = 0.1 * (double) ((((int) package_buffer[252]) * 256)
            + ((int) package_buffer[251]));

    /* success */
    return (0);
}
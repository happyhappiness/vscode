            maxcon = max(maxcon, s.ctime);

            maxtot = max(maxtot, s.time);

            totalcon += s.ctime;

            total += s.time;

        }

        printf("\nConnnection Times (ms)\n");

        printf("              min   avg   max\n");

        printf("Connect:    %5d %5d %5d\n", mincon, totalcon / requests, maxcon);

        printf("Processing: %5d %5d %5d\n", 

            mintot - mincon, (total/requests) - (totalcon/requests),

            maxtot - maxcon);

        printf("Total:      %5d %5d %5d\n", mintot, total / requests, maxtot);

    }

}



/* --------------------------------------------------------- */



/* start asnchronous non-blocking connection */




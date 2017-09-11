            }
        }
        printf("%.2f requests per second\n\n", reqpersec);
    } else if (config.csv) {
        printf("\"%s\",\"%.2f\"\n", config.title, reqpersec);
    } else {
        printf("%s: %.2f requests per second\n", config.title, reqpersec);
    }

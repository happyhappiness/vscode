void
print_partial_compiled_pattern(start, end)
unsigned char *start;
unsigned char *end;
{
    int mcnt, mcnt2;
    unsigned char *p = start;
    unsigned char *pend = end;

    if (start == NULL) {
        printf("(null)\n");
        return;
    }
    /* Loop over pattern commands.  */
    while (p < pend) {
        switch ((re_opcode_t) * p++) {
        case no_op:
            printf("/no_op");
            break;

        case exactn:
            mcnt = *p++;
            printf("/exactn/%d", mcnt);
            do {
                putchar('/');
                printchar(*p++);
            } while (--mcnt);
            break;

        case start_memory:
            mcnt = *p++;
            printf("/start_memory/%d/%d", mcnt, *p++);
            break;

        case stop_memory:
            mcnt = *p++;
            printf("/stop_memory/%d/%d", mcnt, *p++);
            break;

        case duplicate:
            printf("/duplicate/%d", *p++);
            break;

        case anychar:
            printf("/anychar");
            break;

        case charset:
        case charset_not: {
            register int c;

            printf("/charset%s",
                   (re_opcode_t) * (p - 1) == charset_not ? "_not" : "");

            assert(p + *p < pend);

            for (c = 0; c < *p; c++) {
                unsigned bit;
                unsigned char map_byte = p[1 + c];

                putchar('/');

                for (bit = 0; bit < BYTEWIDTH; bit++)
                    if (map_byte & (1 << bit))
                        printchar(c * BYTEWIDTH + bit);
            }
            p += 1 + *p;
            break;
        }

        case begline:
            printf("/begline");
            break;

        case endline:
            printf("/endline");
            break;

        case on_failure_jump:
            extract_number_and_incr(&mcnt, &p);
            printf("/on_failure_jump/0/%d", mcnt);
            break;

        case on_failure_keep_string_jump:
            extract_number_and_incr(&mcnt, &p);
            printf("/on_failure_keep_string_jump/0/%d", mcnt);
            break;

        case dummy_failure_jump:
            extract_number_and_incr(&mcnt, &p);
            printf("/dummy_failure_jump/0/%d", mcnt);
            break;

        case push_dummy_failure:
            printf("/push_dummy_failure");
            break;

        case maybe_pop_jump:
            extract_number_and_incr(&mcnt, &p);
            printf("/maybe_pop_jump/0/%d", mcnt);
            break;

        case pop_failure_jump:
            extract_number_and_incr(&mcnt, &p);
            printf("/pop_failure_jump/0/%d", mcnt);
            break;

        case jump_past_alt:
            extract_number_and_incr(&mcnt, &p);
            printf("/jump_past_alt/0/%d", mcnt);
            break;

        case jump:
            extract_number_and_incr(&mcnt, &p);
            printf("/jump/0/%d", mcnt);
            break;

        case succeed_n:
            extract_number_and_incr(&mcnt, &p);
            extract_number_and_incr(&mcnt2, &p);
            printf("/succeed_n/0/%d/0/%d", mcnt, mcnt2);
            break;

        case jump_n:
            extract_number_and_incr(&mcnt, &p);
            extract_number_and_incr(&mcnt2, &p);
            printf("/jump_n/0/%d/0/%d", mcnt, mcnt2);
            break;

        case set_number_at:
            extract_number_and_incr(&mcnt, &p);
            extract_number_and_incr(&mcnt2, &p);
            printf("/set_number_at/0/%d/0/%d", mcnt, mcnt2);
            break;

        case wordbound:
            printf("/wordbound");
            break;

        case notwordbound:
            printf("/notwordbound");
            break;

        case wordbeg:
            printf("/wordbeg");
            break;

        case wordend:
            printf("/wordend");

        case wordchar:
            printf("/wordchar");
            break;

        case notwordchar:
            printf("/notwordchar");
            break;

        case begbuf:
            printf("/begbuf");
            break;

        case endbuf:
            printf("/endbuf");
            break;

        default:
            printf("?%d", *(p - 1));
        }
    }
    printf("/\n");
}
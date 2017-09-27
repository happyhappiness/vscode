                return;
            if (in.EventType == MOUSE_EVENT
                    && (in.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK))
                return;
        }
        remains = ((start + 30) - time(NULL));
        sprintf (count, "%d...", remains);
        if (!SetConsoleCursorPosition(hConErr, coninfo.dwCursorPosition))
            return;
        if (!WriteConsole(hConErr, count, (DWORD)strlen(count), &result, NULL)
                || !result)
            return;
    }
    while ((remains > 0) && WaitForSingleObject(hConIn, 1000) != WAIT_FAILED);
}

static BOOL  die_on_logoff = FALSE;

static BOOL CALLBACK console_control_handler(DWORD ctrl_type)
{
    switch (ctrl_type)
    {
        case CTRL_BREAK_EVENT:
            fprintf(stderr, "Apache server restarting...\n");

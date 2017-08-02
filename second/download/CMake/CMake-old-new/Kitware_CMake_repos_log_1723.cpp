_snwprintf(filenamew, size, L"%s\\%.*s", handle->dirw,
                file_info->FileNameLength / (DWORD)sizeof(WCHAR),
                file_info->FileName)
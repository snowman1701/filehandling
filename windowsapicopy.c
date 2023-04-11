#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 256
// LPTRSTR stands for pointer and is a pointer
int main(int argc, LPTSTR argv[])
{
    // windows process (handle)
    HANDLE handle_input;
    HANDLE handle_output;

    // DWORD is unsigned 32 bit int
    DWORD bytes_input;
    DWORD bytes_output;

    // how many characters at a time it reads
    char mycharbuffer[BUFFER_SIZE];

    if (argc != 4 || argv[2] != "copy")
    {
        printf("Usage: copy file1 file2\n");
        return 1;
    }
    // opens a file
    // defualt values shown for CreatFile
    //Createfile works on already exsiting files as well
    handle_input = CreateFile(argv[3],
                              GENERIC_READ, // access
                              FILE_SHARE_READ, //share mode
                              NULL, //optional (security)
                              OPEN_EXISTING, //Creatiion dispostion
                              FILE_ATTRIBUTE_NORMAL, // file attributes
                              NULL);// optional
    if (handle_input == INVALID_HANDLE_VALUE)
    {
        printf("[-] Failed to open file. Error: %lu\n", GetLastError());
        return 2;
    }

    //create a handle to open the new file
    handle_output = CreateFile(argv[4],// new file name
                               GENERIC_WRITE,
                               0,
                               NULL,
                               CREATE_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
    if (handle_output == INVALID_HANDLE_VALUE)
    {
        printf("[-] Failure opening output file. Error: %lu\n", GetLastError());
        return 3;
    }

    while (ReadFile(handle_input, // input file handle
                    mycharbuffer, // character array
                    BUFFER_SIZE,  // 256 bytes at a time
                    &bytes_input, // buffer input (optional)
                    NULL /*optional */) && bytes_input > 0)
    {
        WriteFile(handle_output, // specifies which handle to write to
                  mycharbuffer,  // character array
                  bytes_input,   // bytes to write
                  &bytes_output, // bytes written (optional)
                  NULL);         // (optional)
        // checks if the total bytes input and output are the same
        if (bytes_input != bytes_output)
        {
            printf("[-] Something went wrong. Error: %lu\n", GetLastError());
            return 4;
        }
    }
    // closes handles
    CloseHandle(handle_input);
    CloseHandle(handle_output);
    return 0;
}

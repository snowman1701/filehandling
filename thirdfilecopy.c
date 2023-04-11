#include <stdio.h>
#include <windows.h>

int main(int argc, LPTSTR argv[])
{
    if (argc != 4)
    {
        printf("Usage: cpF file1 file2");
        return 1;
    }

    if (!CopyFile(argv[2], argv[3], FALSE))
    {
        printf("Copyfile Error. Error: %lu\n", GetLastError());
        return 2;
    }
    return 0;
}

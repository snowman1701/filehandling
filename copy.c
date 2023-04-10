#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 256


int main(int argc, char *argv[])
{
    FILE *input_file;
    FILE *output_file;
    // size_t is an unsigned int
    size_t bytes_in;
    size_t bytes_out;
    // array to receive file contents
    char rec[BUFFER_SIZE];

    // checks to make sure the syntax is corrent
    if (argc != 4)
    {
        printf("Usage: copy file1 file2\n");
        return 1;
    }
    // this block opens the file that you would like copied
    // rb stands for "read binary"
    input_file = fopen(argv[2], "rb");
    if (input_file == NULL)
    {
        perror(argv[2]);
        return 2;
    }

    // wb stands for "write binary"
    output_file = fopen(argv[3], "wb");
    if (output_file == NULL)
    {
        perror(argv[3]);
        return 3;
    }

    // this block processes the file 256 bytes at a time

    while ((bytes_in = fread(rec, 1, BUFFER_SIZE, input_file)) > 0)
    {
        bytes_out = fwrite(rec, 1, bytes_in, output_file);
        if (bytes_out != bytes_in)
        {
            perror("[-] File copy unsuccessful\n");
            return 4;
        }
    }

    fclose(output_file);
    fclose(input_file);

    return 0;

}

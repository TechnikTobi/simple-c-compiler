int main()
{
    char x, y;
    int file;

    x = 'h';
    y = 'i';
    print(x, y, ' ', 25*2+2, '!', '\n');

    file = file_open("hello_print_write.txt");
    file_write(file, x, y, ' ', 25*2+2, '!', '\n');
    file_close(file);

    exit(0);
}
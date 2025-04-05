int main()
{
    int i, n, size_of_int;
    int *fibs;

    n = 85;
    size_of_int = 8;

    fibs = malloc(n * 8);
    *(fibs + 0 * size_of_int) = 0;
    *(fibs + 1 * size_of_int) = 1;

    for (i = 2; i < n; i++)
    {
        *(fibs + i * size_of_int) = *(fibs + (i-1) * size_of_int) + *(fibs + (i-2) * size_of_int);
    }

    for (i = 0; i < n; i++)
    {
        spike_print(*(fibs + i * size_of_int));
        print('\n');
    }

    exit(0);
}

void spike_print(int n)
{
    int i;
    char c;

    if (n == 0)
    {
        print('0');
        return;
    }

    if (n < 0)
    {
        n = -n;
        print('-');
    }

    i = 1;
    while (n >= i)
    {
        i *= 10;
    }

    while (i > 1)
    {
        i /= 10;
        c = (n / i) % 10 + 48;
        print(c);
    }

    return;
}
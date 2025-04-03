int main()
{
    int i;

    for (i = 0; i < 15; i++)
    {
        spike_print(fib(i));
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

int fib(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    } 
    else 
    {
        return (fib(n-1) + fib(n-2));
    }
}

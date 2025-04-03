int main()
{
    int a;
    int b;

    a = 130;
    b = 124;

    print_regs(_A0, _SP, _S0);

    print('x', ' ');
    spike_print(test(&b));

    print_regs(_A0, _SP, _S0);

    spike_print(a);

    print('\n');
    exit(0);
}

int test(int* n)
{
    
    print_regs(_A0, _SP, _S0);

    print('y', ' ');
    spike_print(*n);
    print('t');
    print('\n');

    return 747;
}

void print_regs(int a0, int sp, int s0)
{
    print('\n', 'a', '0', '=');
    spike_print_hex(a0);
    print(' ', 's', 'p', '=');
    spike_print_hex(sp);
    print(' ', 's', '0', '=');
    spike_print_hex(s0);
    print('\n');
}

void spike_print_hex(int n)
{
    int i;
    int c;

    i = 32 - 4;

    print('0', 'x');

    while (i >= 0)
    {
        c = (n >> i) % 16;
        if (c < 10)
        {
            print(c + 48);
        }
        else
        {
            print((c-10) + 65);
        }

        i -= 4;
    }

    return;
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
int main()
{
    /* The input number that we want to approx. the reverse square root of */
    float number;

    /*
    Declaring the original variables
    Note that long is not supported by this compiler, but as int defaults
    to 32-bit integers this should not be a problem.
    */
    long int i;
    float x2, y;

    /* Setting the input value */
    number = 2.0;

    x2 = number * 0.5;
    y  = number;
    i  = * (int*) &y;
    i  = 0x5f3759df - (i >> 1);
    y  = * (float*) &i;
    y  = y * (1.5 - (x2 * y * y));          /* 1st iteration */
    /* y  = y * (1.5 - (x2 * y * y)); */    /* 2nd iteration, this can be removed */ 

    print(y, '\n');

    exit(0);
}
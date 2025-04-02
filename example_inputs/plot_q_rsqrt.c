int
main
()
{
    /* Declarations */
    int width, height;
    int col_id;
    double x_start, x_end, y_start, y_end;
    double x_res, y_res;
    int x;
    double current_y;
    int file;

    float number;
    long int i;
    float x2, y;

    /* X AXIS IS VERTICAL, Y AXIS IS HORIZONTAL TO MAKE WRITING EASIER! */

    /* User Values */
    width   = 200;
    height  = width;   /* could be something else */
    x_start = 0.001;
    x_end   = 5.123;
    y_start = x_start; /* could be something else */
    y_end   = x_end;

    /* Computed values */
    x_res  = (x_end - x_start) / width;
    y_res  = (y_end - y_start) / height;
    number = x_start;
    col_id = 0;
    x      = 0;

    /* Setup for writing to image file */
    file = file_open("plot_q_rsqrt.ppm");

    /* 
    Write image header:
    P6      # Magic Number
    200 200 # Width and Height in ASCI
    255     # Max brightness
    */
    file_write(file, 'P', '6', '\n', '2', '0', '0', ' ', '2', '0', '0', '\n', '2', '5', '5', '\n');


    current_y = y_end;

    while (x < width)
    {
        col_id = (col_id >= width) ? 0 : col_id;

        number = x * x_res;

        /* Compute the inverse square root */
        x2 = number * 0.5;
        y  = number;
        i  = * (int*) &y;
        i  = 0x5f3759df - (i >> 1);
        y  = * (float*) &i;
        y  = y * (1.5 - (x2 * y * y));          /* 1st iteration */
        y  = y * (1.5 - (x2 * y * y));          /* 2nd iteration, this can be removed */ 

        /* Fill blank rows */
        while (current_y > y)
        {
            while (col_id < width)
            {
                /* Write the RGB values */
                file_write(file, 255, 255, 255);

                /* do NOT use col_id in the condition statement! */
                ++col_id;
            }
            col_id     = 0;
            current_y -= y_res;
        }

        /* Correct row, fill blank space to the left */
        while (col_id++ < x)
        {
            file_write(file, 255, 255, 255);
        }

        /* Write plot point */
        file_write(file, 0, 255, 0);

        ++x;
    }

    /* Account for the "unfinished" row */
    current_y -= y_res;

    /* Fill blank rows */
    while (current_y > y_start)
    {
        while (col_id++ < width)
        {
            /* Write the RGB values */
            file_write(file, 255, 255, 255);
        }
        col_id     = 0;
        current_y -= y_res;
    }

    print('d', 'o', 'n', 'e', '\n');

    /* Close the file & exit */
    file_close(file);
    exit(0);
}
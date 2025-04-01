int
main
()
{
	/* Declarations */
	int width, height;
	int x_id, y_id;
	double x_start, x_end, y_start, y_end;
	double x_res, y_res;

	double x;
	double current_y;

	int red, green, blue;
	int file, print_int;

	float number;
	long int i;
	float x2, y;

	/* X AXIS IS VERTICAL, Y AXIS IS HORIZONTAL TO MAKE WRITING EASIER! */

	/* User Values */
	width  = 200;
	height = 200;
	x_start = 0.001;
	x_end   = 5.123;
	y_start = x_start; /* could be something else */
	y_end   = x_end;

	/* Computed values */
	x_res = (x_end - x_start) / width;  /* Divided by width as rotated by 90°!*/
	y_res = (y_end - y_start) / height; /* Divided by height as rotated by 90°!*/
	number = x_start;

	/* Setup for writing to image file */
	file = file_open("turn_by_90_deg_to_left.ppm");

	/* 
	Write image header:
	P6      # Magic Number
	200 200 # Width and Height in ASCI
	255     # Max brightness
	*/
	file_write(file, 'P', '6', '\n', '2', '0', '0', ' ', '2', '0', '0', '\n', '2', '5', '5', '\n');


	current_y = y_end;

	x_id = 0;

	while (number < x_end)
	{
		print(number);
		print('\n');
		if (x_id >= width)
		{
			x_id = 0;
		}

		/* Compute the inverse square root */
		x2 = number * 0.5;
		y  = number;
		i  = * (int*) &y;
		i  = 0x5f3759df - (i >> 1);
		y  = * (float*) &i;
		y  = y * (1.5 - (x2 * y * y));          /* 1st iteration */
		y  = y * (1.5 - (x2 * y * y));          /* 2nd iteration, this can be removed */ 

		print('y');
		print(y);
		print('\n');

		/* Fill blank rows */
		while (current_y > y)
		{
			while (x_id < width)
			{
				/* Write the RGB values */
				file_write(file, 255, 255, 255);
				x_id = x_id + 1;
			}
			x_id = 0;

			current_y = current_y - y_res;
		}

		/* Correct row, fill blank space to the left */
		while (x_id * x_res < number)
		{
			file_write(file, 255, 255, 255);
			x_id = x_id + 1;
		}

		print('g');
		print('\n');

		/* Write plot point */
		file_write(file, 0, 255, 0);

		number = number + x_res;
	}

	/* Fill blank rows */
	while (current_y > y_start)
	{
		while (x_id < width)
		{
			/* Write the RGB values */
			file_write(file, 255, 255, 255);
			x_id = x_id + 1;
		}
		x_id = 0;

		current_y = current_y - y_res;
	}



	print('d', 'o', 'n', 'e', '\n');

	/* Close the file & exit */
	file_close(file);
	exit(0);
}
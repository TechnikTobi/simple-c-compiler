int
main
()
{
	/* Declarations */
	int width, height;
	int x_id, y_id;
	double x_mid, y_mid;
	double zoom;
	int iteration_counter, max_iterations, raw_pixel_value;
	double x_span, y_span, ppi;
	double x_start, y_end;
	double z_real, z_imag;
	double old_z_real, old_z_imag;
	double c_real, c_imag;
	int red, green, blue;
	int file, print_int;

	/* User Values */
	width  = 200;
	height = 200;
	x_mid  = -1.2;
	y_mid  = 0.1;
	zoom   = 4.0;
	max_iterations = 255;

	/* Computed values */
	x_span = 2.0 / zoom;
	ppi = x_span / width;
	y_span = ppi * height;
	x_start = x_mid - x_span/2.0;
	y_end   = y_mid + y_span/2.0;

	/* Setup for writing to image file */
	file = file_open("mandelbrot.ppm");

	/* 
	Write image header:
	P6      # Magic Number
	200 200 # Width and Height in ASCI
	255     # Max brightness
	*/
	file_write(file, 'P', '6', '\n', '2', '0', '0', ' ', '2', '0', '0', '\n', '2', '5', '5', '\n');

	/* For each row */
	for (y_id = 0; y_id < height; y_id++)
	{
		/* For each column */
		for (x_id = 0; x_id < width; x_id++)
		{
			z_real = 0.0;
			z_imag = 0.0;

			c_real = x_start + ppi * x_id;
			c_imag = y_end - ppi * y_id;

			iteration_counter = 0;

			while (
				z_real * z_real + z_imag * z_imag <= 2*2 &&  /* square threshold */
				iteration_counter++ < max_iterations         /* max iterations */
			)
			{
				old_z_real = z_real;
				old_z_imag = z_imag;

				z_real = old_z_real * old_z_real - old_z_imag * old_z_imag + c_real;
				z_imag = 2 * old_z_real * old_z_imag + c_imag;
			}

			raw_pixel_value = iteration_counter;

			/* 
			Based on the default coloring of the following mandelbrot generator
			https://github.com/TechnikTobi/mandelbrot-rust
			(A private project of mine from a few months ago)
			*/
			if      (  0 <= raw_pixel_value && raw_pixel_value <=  25)
			{
				red   = 10*raw_pixel_value;
				green = 0;
				blue  = 0;
			}
			else if ( 26 <= raw_pixel_value && raw_pixel_value <=  50)
			{
				red   = 255;
				green = 10*(raw_pixel_value-25);
				blue  = 0;
			}
			else if ( 51 <= raw_pixel_value && raw_pixel_value <=  75)
			{
				red   = 255-10*(raw_pixel_value-50);
				green = 255;
				blue  = 0;
			}
			else if ( 76 <= raw_pixel_value && raw_pixel_value <= 100)
			{
				red   = 0;
				green = 255-10*(raw_pixel_value-75);
				blue  = 0;
			}
			else if (101 <= raw_pixel_value && raw_pixel_value <= 125)
			{
				red   = 0;
				green = 0;
				blue  = 10*(raw_pixel_value-100);
			}
			else if (126 <= raw_pixel_value && raw_pixel_value <= 150)
			{
				red   = 0;
				green = 10*(raw_pixel_value-125);
				blue  = 255;
			}
			else if (151 <= raw_pixel_value && raw_pixel_value <= 175)
			{
				red   = 10*(raw_pixel_value-150);
				green = 255;
				blue  = 255;
			}
			else if (176 <= raw_pixel_value && raw_pixel_value <= 200)
			{
				red   = 255;
				green = 255-10*(raw_pixel_value-175);
				blue  = 255;
			}
			else if (201 <= raw_pixel_value && raw_pixel_value <= 225)
			{
				red   = 255;
				green = 0;
				blue  = 255-10*(raw_pixel_value-200);
			}
			else if (226 <= raw_pixel_value && raw_pixel_value <= 255)
			{
				red   = 255-10*(raw_pixel_value-225);
				red   = (red < 0) ? 0 : red;
				green = 0;
				blue  = 0;
			}
			else
			{
				red   = 0;
				green = 0;
				blue  = 0;
			}
			
			/* Write the RGB values */
			file_write(file, red, green, blue);
		}

		/* Print progress - Only works correctly for Spike */
		if (y_id % (height/10) == 0)
		{
			print_int = y_id/2;
			print(
				(print_int >= 10) ? (print_int/ 10)%10 + 48 : ' ', 
				(print_int/  1)%10 + 48, 
				'%', 
				' '
			);
		}

	}

	print('d', 'o', 'n', 'e', '\n');

	/* Close the file & exit */
	file_close(file);
	exit(0);
}
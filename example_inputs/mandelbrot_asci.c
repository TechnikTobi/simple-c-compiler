int
main
()
{
	/* Declarations */
	double x;
	double y;
	
	double x_start;
	double x_end;
	double y_start;
	double y_end;
	
	double scale;

	double z_real;
	double z_imag;

	double old_z_real;
	double old_z_imag;

	double c_real;
	double c_imag;

	int iteration_counter;

	int raw_pixel_value;
	char image_value;
	
	/* Compute the values */
	x_start = -40;
	x_end = 40;
	y_start = -20;
	y_end = 20;
	
	scale = 18;

	/* For each row */
	for(y = y_start; y < y_end; y++)
	{
		/* For each column */
		for(x = x_start; x < x_end; x++)
		{
			z_real = 0.0;
			z_imag = 0.0;

			c_real = x / scale - 0.5;
			c_imag = y / scale;

			iteration_counter = 0;

			while (
				z_real * z_real + z_imag * z_imag <= 2*2 &&  /* square threshold */
				iteration_counter++ < 255                    /* max iterations */
			)
			{
				old_z_real = z_real;
				old_z_imag = z_imag;

				z_real = old_z_real * old_z_real - old_z_imag * old_z_imag + c_real;
				z_imag = 2 * old_z_real * old_z_imag + c_imag;
			}

			/* This line needed to be modified: */
			/* raw_pixel_value = (iteration_counter > 100) ? 3 : (iteration_counter > 5) ? 2 : (iteration_counter > 2) ? 1 : 0; */

			/* New version: */
			raw_pixel_value = (iteration_counter > 101) ? 3 : (iteration_counter > 6) ? 2 : (iteration_counter > 3) ? 1 : 0;

			/* 
			Reason: My compiler first evalues the whole condition-expression
			and then checks the && operation. This means that the postfix
			increment is called *every* time the condition is checked. Other 
			compilers may not visit the postfix increment once it becomes clear
			that the expression can't evaluate to 'true' 
			*/

			/* 
			Map the values to characters 
			This was changed to a chain of if-else due to the lacking support
			for switches
			*/
			if (raw_pixel_value == 0)
			{
				print(' ');
			}
			else if (raw_pixel_value == 1)
			{
				print('.');
			}
			else if (raw_pixel_value == 2)
			{
				print('*');
			}
			else
			{
				print('#');
			}
		}

		print('\n');
	}

	/* 
	The image array now contains image data using ASCII chars
	The result looks something like this:

                          ...................**........                         
                        .....................****........                       
                       ......................****#........                      
                     .......................******..........                    
                    ........................***#***..........                   
                   .......................*****#***...........                  
                   .....................******###***..........                  
                  ....................*******####*******.......                 
                 ....................*********##*********.......                
                ....................*******#########*****........               
                ...................****##############*#***.......               
               ...................******###############***........              
               ...........****..*******################***........              
               ..........*************##################**........              
              ...........************####################**........             
              ...........******#****####################**.........             
              ..........*****#####***####################*.........             
              .........*****#######*####################**.........             
              .....********#############################**.........             
              ..*********#*#############################**.........             
             #########################################****..........            
              ..*********#*#############################**.........             
              .....********#############################**.........             
              .........*****#######*####################**.........             
              ..........*****#####***####################*.........             
              ...........******#****####################**.........             
              ...........************####################**........             
               ..........*************##################**........              
               ...........****..*******################***........              
               ...................******###############***........              
                ...................****##############*#***.......               
                ....................*******#########*****........               
                 ....................*********##*********.......                
                  ....................*******####*******.......                 
                   .....................******###***..........                  
                   .......................*****#***...........                  
                    ........................***#***..........                   
                     .......................******..........                    
                       ......................****#........                      
                        .....................****........                       

	*/

	exit(0);
}
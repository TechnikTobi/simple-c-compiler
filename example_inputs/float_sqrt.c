int main() 
{
	float x, epsilon, guess, prevGuess;

	x = 138.0;
	epsilon = 0.0001;
	guess = x / 2.0;
	prevGuess = 0.0;

	while 
	(
	    (
			prevGuess - guess < epsilon 
			&& guess - prevGuess < epsilon
		) 
		== 0
	)
	{
		prevGuess = guess;
		guess = 0.5 * (guess + x / guess);
	}

	print('S', 'Q', 'R', 'T', ':', ' ', guess, '\n');
}
int main()
{
	int candidate;
	int test;
	int is_prime;
	int remainder;

	for (candidate = 2; candidate < 100; candidate++)
	{
		if 
		(
			candidate % 2 == 0 && candidate > 2
		)
		{
			continue;
		}

		is_prime = 1;

		for (test = 3; test < candidate; test+=2)
		{
			if
			(
				candidate % test == 0
			)
			{
				is_prime = 0;
				break;
			}
		}

		if (is_prime)
		{
			print(candidate);
			print('\n');
		}
	}
}
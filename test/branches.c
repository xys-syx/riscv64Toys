
int main(int argc, char** argv)
{
	printf("1");

	while(1)
	{
		printf("2");
		
		while(2)
		{
			printf("3");
			
			if(3)
				break;
			else if (4)
				continue;
			else
			{
			labb:
				printf("4");
			}
		}

		printf("5");
					
		if(5)
			break;
		else if (6)
			continue;
		else
			printf("6");

		printf("7");

		do
		{
			printf("8");
			if (9)
				break;
		} while(10);

		printf("11");

		if(11)
			break;
		else if (12)
			continue;
		else
		{
			printf("12");
			goto labb;
		}

		printf("13");
		
	}
	
	printf("14");

	
	lab:
	if (a > 3)
	{
		printf("1\n");
	}
	else
	{
		printf("2\n");
		goto lab;
	}

	for (; i < 10;) 
	{
		if (x > b)
			 i += 2;
		else if (2 * 3)
			break;
		else
			continue;
	}

	
	if (1)
		if(2)
			if(3)
				x();
			else
				y();

		else
			z();

	

	if (a > 3)
	{
		printf("1\n");
	}
	else
	{
		printf("2\n");
	}

	while (a < 3)
	{
		printf("3\n");
	}

	printf("Hello!\n");
	
	return 0;
}


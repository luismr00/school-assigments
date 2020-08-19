#include <iostream>
#include <string>
#include <cstring> 
#include "ArrayOfObjects.h"

using namespace std;

//function prototypes
void validateUserInput(int& arraySize, string userInput);

int main()
{
	//code to check for the Circle class
	string userInput = "";
	int numberOfCircles = 0;

	cout << "Enter the number of circles you want created\n";
	getline(cin, userInput);
	validateUserInput(numberOfCircles, userInput);

		try
		{
			//create a vector of circles with "integer" values for the radii
			//the vector is called aVector
			ArrayOfObjects<Circle<int>> aVector(numberOfCircles);
			//create a vector of circles with "double" values for the radii
			//the vector is called bVector
			ArrayOfObjects<Circle<double>> bVector(numberOfCircles);

			//assign values to the raddi of the circles
			for (int x = 0; x < aVector[0].getCircleCount(); x++)
			{
				aVector[x].setCircleRadius(x + 1);
				bVector[x].setCircleRadius(x + 1.1);
			}

			cout << "There are " << aVector[0].getCircleCount() << " circles with the following integer value radii:" << endl;
			for (int x = 0; x < aVector[0].getCircleCount(); x++)
			{
				cout << "Circle " << x + 1 << ": " <<  aVector[x].getCircleRadius() << endl;
			}
			cout << "There are " << aVector[0].getCircleCount() << " circles with the following decimal value radii:" << endl;

			for (int x = 0; x < aVector[0].getCircleCount(); x++)
			{
				cout << "Circle " << x + 1 << ": " << bVector[x].getCircleRadius() << endl;
			}

		}
		catch (ArrayOfObjects<Circle<int>>::ErrorAllocatingPointerMemory e)
		{
			cout << "You entered the following value for the number of circles " << e.getValue() << endl;
			cout << "you want created; this is an illegal value " << endl;
			cout << "and the vector was not created, but the rest of the " << endl;
			cout << "program continues... " << endl << endl;
			cout << "Enter the number of circles you want created\n";
			getline(cin, userInput);
			validateUserInput(numberOfCircles, userInput);
		}
		catch (ArrayOfObjects<Circle<double>>::ErrorAllocatingPointerMemory e)
		{
			cout << "You entered the following value for the number of circles " << e.getValue() << endl;
			cout << "you want created; this is an illegal value " << endl;
			cout << "and the vector was not created, but the rest of the " << endl;
			cout << "program continues... " << endl << endl;
			cout << "Enter the number of circles you want created\n";
			getline(cin, userInput);
			validateUserInput(numberOfCircles, userInput);
		}

		//=========================
		//code for the Rectangle class

		int numberOfRectangles = 0;

		cout << "Enter the number of rectangles you want created\n";
		getline(cin, userInput);

		validateUserInput(numberOfRectangles, userInput);

		try
		{
			//create a vector of Rectangles with "integer" values for its dimensions
			//the vector is called cVector
			ArrayOfObjects<Rectangle<int, int>> cVector(numberOfRectangles);
			//create a vector of Rectangles with "double" values for its dimensions
			//the vector is called dVector
			ArrayOfObjects<Rectangle<double, double>> dVector(numberOfRectangles);
			//create a vector of Rectangles with "int-double" values for its dimensions
			//the vector is called cdVector
			ArrayOfObjects<Rectangle<int, double>> cdVector(numberOfRectangles);

			//assign values to the rectangle dimensions
			for (int x = 0; x < cVector[0].getRectangleCount(); x++)
			{
				cVector[x].setRectangleWidth(x + 1);
				cVector[x].setRectangleLength(x + 2);
				dVector[x].setRectangleWidth(x + 1.1);
				dVector[x].setRectangleLength(x + 2.2);
				cdVector[x].setRectangleWidth(x + 1);
				cdVector[x].setRectangleLength(x + 2.2);
			}

			cout << "There are " << cVector[0].getRectangleCount() << " rectangles with the following integer value dimensions:" << endl;
			for (int x = 0; x < cVector[0].getRectangleCount(); x++)
			{
				cout << "Rectangle " << x + 1 << ": width = " << cVector[x].getRectangleWidth() << endl;
				cout << "Rectangle " << x + 1 << ": length = " << cVector[x].getRectangleLength() << endl;
			}
			
			cout << "There are " << cVector[0].getRectangleCount() << " rectangles with the following decimal value dimensions:" << endl;
			for (int x = 0; x < dVector[0].getRectangleCount(); x++)
			{
				cout << "Rectangle " << x + 1 << ": width = " << dVector[x].getRectangleWidth() << endl;
				cout << "Rectangle " << x + 1 << ": length = " << dVector[x].getRectangleLength() << endl;
			}

			cout << "There are " << cVector[0].getRectangleCount() << " rectangles with the following \"int-decimal\" value dimensions:" << endl;
			for (int x = 0; x < dVector[0].getRectangleCount(); x++)
			{
				cout << "Rectangle " << x + 1 << ": width = " << cdVector[x].getRectangleWidth() << endl;
				cout << "Rectangle " << x + 1 << ": length = " << cdVector[x].getRectangleLength() << endl;
			}

		}
		catch (ArrayOfObjects<Rectangle<int, int>>::ErrorAllocatingPointerMemory e)
		{
			cout << "You entered the following value for the number of rectangles " << e.getValue() << endl;
			cout << "you want created; this is an illegal value " << endl;
			cout << "and the vector was not created, but the rest of the " << endl;
			cout << "program continues... " << endl << endl;
			cout << "Enter the number of rectangles you want created\n";
			getline(cin, userInput);

			validateUserInput(numberOfRectangles, userInput);
		}
		catch (ArrayOfObjects<Rectangle<double, double>>::ErrorAllocatingPointerMemory e)
		{
			cout << "You entered the following value for the number of rectangles " << e.getValue() << endl;
			cout << "you want created; this is an illegal value " << endl;
			cout << "and the vector was not created, but the rest of the " << endl;
			cout << "program continues... " << endl << endl;
			cout << "Enter the number of rectangles you want created\n";
			getline(cin, userInput);

			validateUserInput(numberOfRectangles, userInput);
		}

		cout << "\n\nchecking nested exception classes\n";
		//checking nested exception classes
		try
		{
			Circle<int> axVector(-1);

		}
		catch (Circle<int>::ErrorAllocatingMemory e)
		{
			cout << "You entered the following value for the radius " << e.getValue() << endl;
			cout << "This is an illegal value " << endl;
			cout << "and the circle was not created, but the rest of the " << endl;
			cout << "program continues... " << endl;
		}

		cout << endl;
		try
		{
			Rectangle<int, int> cxVector(-2,1);

		}
		catch (Rectangle<int, int>::ErrorAllocatingLengthOrWidth e)
		{
			cout << "You entered the following value for the rectangle " << e.getValue() << endl;
			cout << "This is an illegal value for one of the rectangle dimensions" << endl;
			cout << "and the rectangle was not created, but the rest of the " << endl;
			cout << "program continues... " << endl;
		}

		cout << endl;
		try
		{
			Rectangle<int, int> cxVector(2, -3);

		}
		catch (Rectangle<int, int>::ErrorAllocatingLengthOrWidth e)
		{
			cout << "You entered the following value for the rectangle " << e.getValue() << endl;
			cout << "This is an illegal value for one of the rectangle dimensions" << endl;
			cout << "and the rectangle was not created, but the rest of the " << endl;
			cout << "program continues... " << endl;
		}
		
	system("pause");

	return 0;
}
//fuction definitions
void validateUserInput(int& arraySize, string userInput)
{
	int counter = 0;
	while (counter < userInput.length() || userInput.length() == 0)
	{
		if (!isdigit(userInput[counter]))
		{
			cout << "Invalid entry\n";
			cout << "Enter a positive integer\n";
			getline(cin, userInput);
			counter = 0;
		}
		else
		{
			counter++;
		}
	}
	arraySize = atoi(userInput.c_str());
}

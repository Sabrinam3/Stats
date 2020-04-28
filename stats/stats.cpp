/*
Sabrina Tessier
May 31, 2018
Stats project
*/
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <locale>
using namespace std;

//Function declaration headers
void quicksort(vector<double> &v, int low, int high);
double findMin(vector<double> const &v);
double findMax(vector<double> const &v);
double calcMean(vector<double> const &v);
double calcMedian(vector<double> const &v);
vector<double>findModes(vector<double> const &v);
string printModes(vector<double> const &v);
double calcMeanDeviation(vector<double> const &v);
double calcMedianDeviation(vector<double> const &v);
double calcVariance(vector<double> const &v);
double calcStandardDeviation(vector<double> const &v);
void printFrequencyTable(vector<double> const &v);
string calcModeDeviation(vector<double> const &v);
double calcSubsetMean(vector<double> const &v, int beginIndex, int endIndex);
void printQuintileMeans(vector<double> const &v);
void outlierReport(vector<double> const &v);


int main()
{
	//Set the locale so output will have thousands seperators
	locale here("");
	cout.imbue(here);

	//Welcome Message and Program Description
	cout << "Stats, (c) 2018 Sabrina Tessier" << endl;
	cout << "Enter white-space separated data values terminated by ^Z" << endl;
	//Declare the vector
	vector<double> inputVector;
	//A variable to hold the inputs
	double i;
	//A variable to count the number of datapoints
	int numberDataPoints = 0;
	//While cin can read values into i
	while (cin >> i)
	{
		//Add the numbers to the vector
		inputVector.push_back(i);
		//As the values are being added, count them
		numberDataPoints++;
	}
	cout << "Results: " << endl;
	//Print the number of data points
	cout << "N= " << fixed << setprecision(3) << numberDataPoints << endl;

	//If the dataset is empty, no other calculations can be done. Report this to the user
	if (numberDataPoints == 0)
	{
		cout << "Empty data set!" << endl;
	}

	//If the dataset is not empty, we can perform the other calculations
	else
	{
		//Sort the vector
		quicksort(inputVector, 0, inputVector.size() - 1);

		//Find and print the minimum value
		cout << "Min= " << fixed << setprecision(3) << findMin(inputVector) << endl;

		//Find and print the maximum value
		cout << "Max= " << fixed << setprecision(3) << findMax(inputVector) << endl;

		//Calculate and print the arithmetic mean
		cout << "Arithmetic mean = " << fixed << setprecision(3) << calcMean(inputVector) << endl;

		//Calculate and print the median
		cout << "Statistical median = " << fixed << setprecision(3) << calcMedian(inputVector) << endl;

		//Calculate and print the modes
		cout << printModes(inputVector);

		//Calculate and print the mean absolute deviation
		cout << "Mean absolute deviation = " << calcMeanDeviation(inputVector) << endl;

		//Calculate and print the median absolute deviation
		cout << "Median absolute deviation = " << fixed << setprecision(3) << calcMedianDeviation(inputVector) << endl;

		//Calculate and print the mode absolute deviation
		cout << "Mode absolute deviation = " << calcModeDeviation(inputVector) << endl;

		//Calculate and print the variance
		cout << "Variance = " << fixed << setprecision(3) << calcVariance(inputVector) << endl;

		//Calculate and print the standard deviation
		cout << "Standard deviation = " << fixed << setprecision(3) << calcStandardDeviation(inputVector) << "\n\n";

		//Print the frequency distribution table
		printFrequencyTable(inputVector);

		//Print the Quintile Means
		printQuintileMeans(inputVector);

		//Print the outlier report
		outlierReport(inputVector);
	}//end else
}//end main

/*
 Function Name: quicksort
 Purpose: sorts a vector of doubles using the quicksort method 
 Accepts: A vector (as a reference since the values need to be changed)
 Returns: Nothing
 */

void quicksort(vector<double> &v, int low,  int high)
{
	//Calculate the midpoint
	int mid = (low + high) / 2;
	//Temp variables that can be moved
	 int i = low;
	 int j = high;
	//Pivot value
	double pivot = v[mid];
	//Loop until i is greater than j
	while (i <= j)
	{
		//Shuffle i over until it's value is greater than the mid value
		while (v[i] < pivot)
		{
			i++;
		}

		//Shuffle j over until its value is less than the mid value
		while (v[j] > pivot)
		{
			j--;
		}

		if (i <= j)
		{
			double temp = v[i];
			v[i] = v[j];
			v[j] = temp;
			i++;
			j--;
		}//end if
	}//end while

	 //Recursively call quick sort
	if (low < j)
	{
		quicksort(v, low, j);
	}//end if
	if (i < high)
	{
		quicksort(v, i, high);
	}//end if
}//end function

/*
Function Name: findMin
Purpose: Finds the minimum value in the data set
Accepts: A vector
Returns: The smallest value of the vector i.e. the first element in the sorted array
*/

double findMin(vector<double> const &v)
{
	return v[0];
}//end function

 /*
 Function Name: findMax
 Purpose: Finds the maximum value in the data set
 Accepts: A vector
 Returns: The largest value of the vector i.e. the last element in the sorted array
 */
double findMax(vector<double> const &v)
{
	return v[v.size()-1];
}//end function

/*
Function Name: calcMean
Purpose: Finds the arithmetic mean of a data set
Accepts: a vector of doubles
Returns: a double - the mean of the dataset
*/
double calcMean(vector<double> const &v)
{
	//Variable to hold the total of the values in the vector
	double sum = 0;

	//Loop through vector and add up all the elements 
	for (double a : v)
	{
		sum += a;
	}

	//Find the average of the values and return
	return sum / v.size();	
}//end function

/*
Function Name: calcMedian
Purpose: calculates the median of the dataset
Accepts: a vector of doubles
Returns: the statistical median
*/
double calcMedian(vector<double> const &v)
{
	//If number of datapoints is even, median is the element at (size/2) plus
	//the element at (size/2) - 1, divided by 2
	if (v.size() % 2 == 0)
	{
		//the first value 
		double value1 = v[v.size() / 2];
		//the second value 
		double value2 = v[(v.size() / 2) - 1];
		return (value1 + value2) / 2;	
	}
	//if number of datapoints is odd, median is the element at length/2 casted to an integer so the decimal is truncated 
	else
	{
		return v[(int)v.size() / 2];	
	}
}//end function

/*Function Name: findModes
Purpose: Finds the mode(s) in a dataset
Accepts: a vector of doubles(by reference)
Returns: a vector with the mode or modes
*/

vector<double>findModes(vector<double> const &v)
{
	//counter variables
	unsigned int maxCount = 1;
	unsigned int currentCount = 1;
	unsigned int uniqueNumberCounter = 1;
	//vector to hold the mode or modes
	vector<double>modes;

	//Loop through the vector
	for ( unsigned int i = 0; i < v.size() - 1; ++i)
	{
		//index variables
		unsigned int currentIndex = i;
		unsigned int nextIndex = i + 1;
		if (v[currentIndex] == v[nextIndex])
		{
			//Repeating values, so increment counter
			currentCount++;
		}//end if
		else
		{
			//A unique number has been found so reset counter and increment unique number counter
			currentCount = 1;
			uniqueNumberCounter++;
		}//end else
		if (currentCount == maxCount)
		{
			//Add value to modes vector
			modes.push_back(v[i]);
		}//end if
		else if (currentCount > maxCount)
		{
			//the current count becomes the new max count
			maxCount = currentCount;
			//clear the vector of current values and replace with the larger occuring value
			modes.clear();
			modes.push_back(v[i]);
		}//end if
	}//end for

	//If the maxCount is 1 i.e. all values occur once, add the last value of the vector to the modes vector (this solves the index out of bounds problem)
	if (maxCount == 1)
	{
		modes.push_back(v[v.size() - 1]);
	}//end if

	//If the number of unique values equals the number of modes, all values occur the same amount of times and there is no mode, so clear the mode vector
	if (uniqueNumberCounter == modes.size())
	{
		modes.clear();
	}//end if
	return modes;
}//end function



/*
Function Name: printModes
Purpose: Converts the modes of a dataset to a formatted string
Accepts: a vector of doubles that contains the modes of a dataset
Returns: A formatted string of the modes
*/
string printModes(vector<double> const &v)
{
	//Set the locale so that thousands seperators will be in place
	locale here("");
	stringstream ss;
	//Apply the locale to the stringstream
	ss.imbue(here);
	//Use the findModes function to get the modes of the vector
	vector<double> modes = findModes(v);
	//Checks if the mode vector is empty meaning there is no mode
	ss << "Mode = ";
	if (modes.empty())
	{
		ss << "No Mode" << endl;
	}
	//There are modes in the dataset, so format them properly
	else
	{
		ss << "{ ";
		for (unsigned i = 0; i < modes.size(); ++i)
		{
			if (modes.size() == 1)
			{
				ss << fixed << setprecision(3) << modes[0] << " }" << endl;
			}
			else if (i == modes.size() - 1)
			{
				ss << fixed << setprecision(3) << modes[i] << " }" << endl;
			}
			else
			{
				ss << fixed << setprecision(3) << modes[i] << ", ";
			}
		}//end for
	}//end else
	//Convert ss to a string
	string modeString = ss.str();
	//Return the string
	return modeString;
}//end function

 /*
 Function Name: meanDeviation
 Purpose: Calculates the mean absolute deviation for the dataset
 Accepts: a vector of double values
 Returns: the mean absolute deviation
 */
double calcMeanDeviation(vector<double> const &v)
{
	//find the mean of the dataset
	double mean = calcMean(v);
	//Variables to hold the total of the differences and the difference of each value from the mean
	double totalDifferences = 0; 
	double difference = 0; 
	//Loop through the vector and sum the difference of each datapoint from the mean
	for (unsigned i = 0; i < v.size(); ++i)
	{
		difference = abs(v[i] - mean);
		totalDifferences += difference;
	}
	//Find and return the mean absolute deviation
	return totalDifferences / v.size();
}//end function

/*
Method Name: calcMedianDeviation
Purpose: calculates the median absolute deviation
Accepts: a vector of doubles
Returns: the median absolute deviation
*/

double calcMedianDeviation(vector<double> const &v)
{
	//find the median of the dataset
	double median = calcMedian(v);
	//substract the median from each data point, find the absolute value, and add to a sum variable
	double sum = 0; 
	for (unsigned i = 0; i < v.size(); ++i)
	{
		sum += abs(v[i] - median);
	}
	//Find and return the absolute median 
	return sum / v.size();
}//end function

/*
Function Name: calcModeDeviation
Purpose: Calculates the mode absolute deviation of a dataset
Accepts: a vector of doubles
Returns : a string representing the mode absolute deviation (if it can be calculated), or a string saying the calculation is not possible
*/
string calcModeDeviation(vector<double> const &v)
{
	//Locale for thousands seperators
	locale here("");
	//stringstream to hold data
	stringstream ss;
	//Apply locale to stringstream
	ss.imbue(here);
	//Get the mode(s) using the findModes function
	vector<double> modes = findModes(v);
	//If there is no mode, or if there is more than one mode, the calculation cannot be done
	if (modes.size() > 1 || modes.empty())
	{
		ss << "N/A (No Unique Mode)";
	}//end if
	//There is a mode so we will find the absolute difference of each data value from the mode and then average it
	else
	{
		//Accumulator variable
		double sum = 0;
		for (unsigned i = 0; i < v.size(); ++i)
		{
			sum += abs(v[i] - modes[0]);
		}//end for

		//Put the mode deviation into the stringstream
		ss << fixed << setprecision(3) << sum / v.size();
	}//end else
	
	//Convert ss to a string
	string modeDeviation = ss.str();
	//return the string
	return modeDeviation;
}//end function

/*
Function Name: calcVariance
Purpose: Calculates and prints the variance of the dataset
Accepts: a vector of doubles
Returns: a double
*/
double calcVariance(vector<double> const &v)
{
	//Find the mean of the dataset
	double mean = calcMean(v);
	//subtract the mean from each datapoint, square the difference, and add these to an accumulator variable
	double sum = 0;
	for (double a : v)
	{
		sum += (a - mean) * (a - mean);
	}//end for
	//Find and return the variance
	return sum / v.size();	
}//end function

 /*
 Function Name: calcStandardDeviation
 Purpose: calculates the standard deviation of a dataset
 Accepts: A vector of doubles
 Returns: The standard deviation of the dataset
 */
double calcStandardDeviation(vector<double> const &v)
{
	//First calculate the variance and use it to find the standard deviation
	double variance = calcVariance(v);
	//Calculate the standard deviation by getting the square root of the variance
	 return sqrt(variance);	
}//end function

/*
Function Name: printFrequencyTable
Purpose: prints the frequency distribution table with help from the createBins, frequencyDistribution, and calcPercent functions
Accepts: a vector of doubles
Returns: nothing
*/
void printFrequencyTable(vector<double> const &v)
{
	//Find the range of the dataset
	double range = v[v.size() - 1] - v[0];
	//If the range is 0 i.e. all the value(s) in the vector are the same
	if (range == 0)
	{
		for (unsigned int i = 0; i < 10; ++i)
		{
			cout << "[ ";
			if (i == 0)
			{
				cout << fixed << setprecision(2) <<  v[0] << "..  " << fixed << setprecision(2) << v[0] << ") = " << v.size() << " : " << 1.00 << endl;
			}
			else {
				cout << fixed << setprecision(2) << v[0] << "..  " << fixed << setprecision(2) << v[0] << ") = " << 0 << " : " << 0.00 << endl;
			}
		}
	}
	else
	{
		//Find out how much "padding" should be added to each bin
		double amountToAdd = range / 10 / (range + 1);
		//Calculate the binWidth
		double binWidth = range / 10 + amountToAdd;
		//index variable used to parse vector
		int index = 0;
		//boolean that checks if the whole vector has been parsed
		bool finished = false;
		//begin and end values used to compare values
		double begin = v[0];
		double end = begin + binWidth;

		//While the vector has not been fully parsed 
		while (!finished)
		{
			//Counter to keep track of how many values fall within range
			int counter = 0;

			//while the value at current index falls within range
			while (v[index] >= begin && v[index] < end)
			{
				counter++;
				index++;
				//If final index has been reached, exit loop and print final bin
				if (index == v.size())
				{
					finished = true;
					break;
				}
			}//end while
			 //stringstream to format output nicely
			stringstream iss;
			//Locale for thousands seperators
			locale here("");
			//Apply locale to stringstream
			iss.imbue(here);
			//Push 'bin' data into stringstream
			iss << fixed << setprecision(2) << " " << begin << ".. " << fixed << setprecision(2) << end << ") = ";
			//Print the results
			cout << "[ " << fixed << setw(18) << iss.str() << counter << " : " << fixed << setprecision(2) << (double)counter / v.size() << endl;
			//The new value of begin is what end was before
			begin = end;
			//The new value of end is end + binWidth
			end = end + binWidth;
		}//end while
	}
}//end function

/*
Function Name: calcSubsetMean
Purpose: Calculates the mean of a subset of the data
Accepts: a vector of doubles, the starting index, the ending index
Returns: the mean of the values
*/
double calcSubsetMean(vector<double> const &v, int beginIndex, int endIndex)
{
	//Accumulator variable
	double sum = 0;
	for (int i = beginIndex; i < endIndex; ++i)
	{
		sum += v[i];
	}//end for

	//Return the subset average
	return (double)sum / (endIndex - beginIndex);
}//end function

/*
Function Name: printQuintileMeans
Purpose: Divides the data set into 5 "quintiles", then finds the mean of each quintile.
		 Also prints the indexes that were used for each quintile
Accepts: a vector of doubles
Returns: Nothing
*/
void printQuintileMeans(vector<double> const &v) 
{
	cout << "\nQuintile Means" << endl;
	//If there are less than 5 datapoints, we cannot do the calculation. Print this to the console.
	if (v.size() < 5)
	{
		cout << "\nNo quintiles to compute, there are less than 5 samples." << endl;
	}
	else
	{
		 int begin = 0;
		 int end = 0;
		for (unsigned int i = 0; i < 5; ++i)
		{
			//calculate the beginning and end index
			begin = static_cast<int>(floor(v.size() * (double)(i / 5.00)));
			end = static_cast<int>(floor(v.size() * (double)(i + 1) / 5.00));
			//Calculate the mean of that subset
			double mean = calcSubsetMean(v, begin, end);
			//Print the result
			cout << "Q" << i + 1 << ": " << fixed << setw(8) << setprecision(3) << mean << " [" << begin << ".." << end << ")" << endl;
		}//end for
	}//end else
	
	
}//end function

/*
Function Name: outlierReport
Purpose: calculates and determines the number of data points that are above and below 2 and 3 standard deviations of the mean
Accepts: a vector of doubles
Returns: Nothing
*/
void outlierReport(vector<double> const &v)
{
	//If the range is 0, i.e. all the elements in the vector are the same, report that there are no outliers
	if (v[v.size() - 1] - v[0] == 0)
	{
		cout << "There are no outliers.\n" << endl;
	}
	else
	{
		//find the mean
		double mean = calcMean(v);
		//find the standard deviation
		double stdDev = calcStandardDeviation(v);
		int threeBelow = 0;
		int twoBelow = 0;
		int twoAbove = 0;
		int threeAbove = 0;
		//Values that each value in vector will be compared to
		double twoBelowDev = mean - stdDev * 2;
		double threeBelowDev = mean - stdDev * 3;
		double twoAboveDev = mean + stdDev * 2;
		double threeAboveDev = mean + stdDev * 3;
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			if (v[i] <= threeBelowDev)
			{
				threeBelow++;
			}
			else if (v[i] <= twoBelowDev)
			{
				twoBelow++;
			}
			else if (v[i] >= twoAboveDev)
			{
				twoAbove++;
			}
			else if (v[i] >= threeAboveDev)
			{
				threeAbove++;
			}
		}//end for

		//Print the results
		cout << "\n\nOutliers\n-------------" << endl;
		cout << "<= 3 dev below: " << threeBelow << " (" << fixed << setprecision(2) << threeBelow / v.size() << "%)" << endl;
		cout << "<= 2 dev below: " << twoBelow << " (" << fixed << setprecision(2) << twoBelow / v.size() << "%)" << endl;
		cout << ">= 2 dev above: " << twoAbove << " (" << fixed << setprecision(2) << twoAbove / v.size() << "%)" << endl;
		cout << ">= 3 dev above: " << threeAbove << " (" << fixed << setprecision(2) << threeAbove / v.size() << "%)" << endl;
	}//end else
}//end function


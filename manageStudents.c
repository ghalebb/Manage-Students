#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/**
 * @def MAX_TEMPERATURE_CS 300
 * @brief A macro that sets the maximal temperature.
 */
#define FIELD_LENGTH 43

/**
 * @def MAX_TEMPERATURE_CS 300
 * @brief A macro that sets the maximal temperature.
 */
#define LINE_LENGTH 61

/**
 * @def MAX_TEMPERATURE_CS 300
 * @brief A macro that sets the maximal temperature.
 */
#define TERMINATE_PROGRAM 'q'

/** the input array*/
char input[LINE_LENGTH];

/**
 * @def MAX_TEMPERATURE_CS 300
 * @brief A macro that sets the maximal temperature.
 */
typedef struct Student
{
	long id;
	int grade, age;
	char country[FIELD_LENGTH];
	char city[FIELD_LENGTH];
	char name[FIELD_LENGTH];
} Student;


/**
 * @brief This function checks if a given string is alphabetic or - or a space
 * @return 0, to tell the system the string is legal.
 */
int checkName(char name[])
{
	int n = strlen(name);
	for (int i = 0; i < n; i++)
	{
		if ((isalpha(name[i])) ||
			name[i] == ' ' || name[i] == '-')
		{
			continue;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief Checks if a given name is composed from english alphabet.
 * @return 0, to tell the system the string is legal.
 */
int checkCountry(char toCheck[])
{
	for (int i = 0, n = strlen(toCheck); i < n; i++)
	{
		if ((isalpha(toCheck[i])) ||
			toCheck[i] == '-')
		{
			continue;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}


/**
 * @brief Checks if a given name is composed from english alphabet or \n.
 * @return 0, to tell the system the string is legal.
 */
int checkCity(char toCheck[])
{
	for (int i = 0, n = strlen(toCheck); i < n; i++)
	{
		if ((isalpha(toCheck[i])) ||
			toCheck[i] == '-' || toCheck[i] == '\n')
		{
			continue;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief This function checks if the inserted fields of a students are legal
 * @return 1 if the fields are legal, 0 otherwise.
 */
int checkFields(Student temporaryStudent, int currentLine)
{
	if (temporaryStudent.id > 9999999999 || temporaryStudent.id < 1000000000)
	{
		printf("ERROR: id must be a 10 digits number that does not start with 0\nin line %d\n",
			   currentLine);
		return 0;
	}
	else if (checkName(temporaryStudent.name))
	{
		printf("ERROR: name can only contain alphabetic characters, whitespaces or '-'\n"
			   "in line %d\n", currentLine);
		return 0;
	}
	else if (temporaryStudent.grade < 0 || temporaryStudent.grade > 100)
	{
		printf("ERROR: grade must be an integer between 0 and 100\nin line %d\n", currentLine);
		return 0;
	}
	else if (temporaryStudent.age < 18 || temporaryStudent.age > 120)
	{
		printf("ERROR: age must be an integer between 18 and 120\nin line %d\n", currentLine);
		return 0;
	}
	else if (checkCountry(temporaryStudent.country))
	{
		printf("ERROR: country can only contain alphabetic characters or '-'\nin line %d\n",
			   currentLine);
		return 0;
	}
	else if (checkCity(temporaryStudent.city))
	{
		printf("ERROR: city can only contain alphabetic characters or '-'\nin line %d\n",
			   currentLine);
		return 0;
	}
	return 1;
}

/**
 * @brief The main function of the finding the best student.
 */
void findBest()
{
	Student temporaryStudent, bestStudent;

	float bestAvg = -1;

	printf("Enter student info. To exit press q, then enter\n");

	fgets(input, LINE_LENGTH, stdin);

	int res = sscanf(input, "%ld,%42[^,],%d,%d,%42[^,],%s\n", &temporaryStudent.id,
					 temporaryStudent.name,
					 &temporaryStudent.grade,
					 &temporaryStudent.age, temporaryStudent.country, temporaryStudent.city);
	int currentLine = 0;

	while (input[0] != TERMINATE_PROGRAM && input[1] != '\n')
	{
		if (res != 6)
		{
			printf("ERROR: info must match specified format\n"
				   "in line %d\n",
				   currentLine);
		}
		else if (checkFields(temporaryStudent, currentLine) &&
				 ((float) temporaryStudent.grade / (float) temporaryStudent.age) > bestAvg)
		{
			bestAvg = ((float) temporaryStudent.grade / (float) temporaryStudent.age);
			bestStudent = temporaryStudent;
		}

		printf("Enter student info. To exit press q, then enter\n");
		currentLine++;
		fgets(input, LINE_LENGTH, stdin);
		res = sscanf(input, "%ld,%42[^,],%d,%d,%42[^,],%s\n", &temporaryStudent.id,
					 temporaryStudent.name,
					 &temporaryStudent.grade,
					 &temporaryStudent.age, temporaryStudent.country, temporaryStudent.city);


	}
	if (bestAvg != -1)
	{
		printf("best student info is: %ld,%s,%d,%d,%s,%s\n", bestStudent.id,
			   bestStudent.name, bestStudent.grade, bestStudent.age,
			   bestStudent.country, bestStudent.city);
	}

}


/**
 * @brief this function swaps the values of the given Students.
 * */
void swap(Student *a, Student *b)
{
	Student temp = *a;
	*a = *b;
	*b = temp;
}

/** @brief the partition function of quick sort*/
int partition(Student student[], int low, int high)
{
	Student pivot = student[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (strcmp(student[j].name, pivot.name) < 0)
		{
			i++;
			swap(&student[i], &student[j]);
		}
	}
	swap(&student[i + 1], &student[high]);
	return (i + 1);
}

/**
 * @brief Quicksort function, which sorts the given students according to their name.
 * */

void quickSort(Student students[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(students, low, high);

		quickSort(students, low, pi - 1);
		quickSort(students, pi + 1, high);

	}

}


/**
 *@brief MergeSort function, which sorts the given students according to their grades
 */
void merge(Student studentsArray[], int left, int middle, int right)
{
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	Student L[2750];
	Student R[2750];

	for (i = 0; i < n1; i++)
	{
		L[i] = studentsArray[left + i];
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = studentsArray[middle + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2)
	{
		if (L[i].grade <= R[j].grade)
		{
			studentsArray[k] = L[i];
			i++;
		}
		else
		{
			studentsArray[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		studentsArray[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		studentsArray[k] = R[j];
		j++;
		k++;
	}

}

/**
 * @brief merge sort function
 */
void mergeSort(Student studentsMerge[], int left, int right)
{
	if (left < right)
	{
		int middle = left + (right - left) / 2;
		mergeSort(studentsMerge, left, middle);
		mergeSort(studentsMerge, middle + 1, right);
		merge(studentsMerge, left, middle, right);
	}
}

/**
 * @brief The main function. it calls one of the three functions.
 */
void sort(int n)
{
	Student studentsArray[5500];
	Student temporaryStudent;
	int studsNum = 0;
	printf("Enter student info. To exit press q, then enter\n");
	fgets(input, LINE_LENGTH, stdin);

	int res = sscanf(input, "%ld,%[^,],%d,%d,%[^,],%s\n", &temporaryStudent.id,
					 temporaryStudent.name,
					 &temporaryStudent.grade, &temporaryStudent.age,
					 temporaryStudent.country, temporaryStudent.city);
	int currentLine = 0;
	while (input[0] != TERMINATE_PROGRAM && input[1] != '\n')
	{
		if (res != 6)
		{
			printf("ERROR: info must match specified format\n"
				   "in line %d\n",
				   currentLine);
		}

		else if (checkFields(temporaryStudent, currentLine))
		{
			studentsArray[studsNum] = temporaryStudent;
			studsNum++;
		}

		printf("Enter student info. To exit press q, then enter\n");

		currentLine++;
		fgets(input, LINE_LENGTH, stdin);
		res = sscanf(input, "%ld,%[^,],%d,%d,%[^,],%s\n", &temporaryStudent.id,
					 temporaryStudent.name,
					 &temporaryStudent.grade,
					 &temporaryStudent.age, temporaryStudent.country, temporaryStudent.city);
	}
	if (studsNum != 0 && n == 1)
	{
		mergeSort(studentsArray, 0, studsNum - 1);
		for (int i = 0; i < studsNum; i++)
		{
			printf("%ld,%s,%d,%d,%s,%s\n", studentsArray[i].id, studentsArray[i].name,
				   studentsArray[i].grade,
				   studentsArray[i].age,
				   studentsArray[i].country, studentsArray[i].city);
		}
	}
	if (studsNum != 0 && n == 2)
	{
		quickSort(studentsArray, 0, studsNum - 1);
		for (int i = 0; i < studsNum; i++)
		{
			printf("%ld,%s,%d,%d,%s,%s\n", studentsArray[i].id, studentsArray[i].name,
				   studentsArray[i].grade,
				   studentsArray[i].age,
				   studentsArray[i].country, studentsArray[i].city);
		}
	}

}

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("USAGE: sortStudents <action>\n");
		return 1;
	}
	if (strcmp(argv[1], "best") == 0)
	{
		findBest();
	}
	else if (strcmp(argv[1], "merge") == 0)
	{
		sort(1);
	}
	else if (strcmp(argv[1], "quick") == 0)
	{
		sort(2);
	}
	else
	{
		printf("USAGE:  sortStudents <action>\n");
		return 1;
	}
	return 0;
}




